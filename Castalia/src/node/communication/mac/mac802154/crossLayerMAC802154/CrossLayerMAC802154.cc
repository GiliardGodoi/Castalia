#include "CrossLayerMAC802154.h"

Define_Module(CrossLayerMAC802154);

void CrossLayerMAC802154::startup()
{
    window = par("window");

    currentAckCount = 0;
    currentPacketCount = 0;
    sequenceRecordedTaxaMAC = 0;

    totalMACPacketsTransmitted = 0;
    totalMACAcksReceived = 0;

    return Basic802154::startup();
}

void CrossLayerMAC802154::timerFiredCallback(int index) {
    switch (index)
    {
        case ACK_TIMEOUT:
            /* code */
            trace() << "ACK timeout disparado ";
            setAckResult(0); // failed
            break;
    }
    Basic802154::timerFiredCallback(index);
}

void CrossLayerMAC802154::finishSpecific() {

    if(!isPANCoordinator)
    {
        declareOutput("TaxaMAC evaluation");
        collectOutput("TaxaMAC evaluation", "Total, total ACKS", totalMACAcksReceived);
        collectOutput("TaxaMAC evaluation", "Total, total Packets", totalMACPacketsTransmitted);
        
        collectOutput("TaxaMAC evaluation", "Counter, countACK", currentAckCount);
        collectOutput("TaxaMAC evaluation", "Counter, packetCount", currentPacketCount);
        collectOutput("TaxaMAC evaluation", "Counter, recorded taxaMAC", sequenceRecordedTaxaMAC);
    }
    
    return Basic802154::finishSpecific();
}


/**
 * REIMPLEMENTATIONS FROM 802.15.4 METHODS 
 */

void CrossLayerMAC802154::handleAckPacket(Basic802154Packet * rcvPacket, double rssi, double lqi)
{
    if(currentPacket != NULL)
    {
        switch (currentPacket->getMac802154PacketType())
        {
            case MAC_802154_DATA_PACKET:
                if(currentPacket->getSeqNum() == rcvPacket->getSeqNum()){
                    if(SELF_MAC_ADDRESS != 0) {
                        setAckResult(1);
                    }
                }
                break;
        }

    }
    Basic802154::handleAckPacket(rcvPacket,rssi,lqi);
}


/* Transmit a packet by sending it to the radio */
void CrossLayerMAC802154::transmitCurrentPacket()
{
	if (currentPacket == NULL) {
		trace() << "WARNING: transmitCurrentPacket() called while currentPacket == NULL";
		return;
	}
	
	//check if transmission is allowed given current time and tx time
	simtime_t txTime = TX_TIME(currentPacket->getByteLength()) + currentPacketResponse;
	simtime_t txEndTime = getClock() + txTime;
	int allowTx = 1;
	
	if (macState == MAC_STATE_CAP) {	//currently in CAP
		if (currentFrameStart + CAPend < txEndTime && CAPend != GTSstart)
			//transmission will not fit in CAP 
			allowTx = 0;
	} else if (macState == MAC_STATE_GTS) {	//currently in GTS
		if (currentFrameStart + GTSend < txEndTime)
			//transmission will not fit in GTS
			allowTx = 0;
	}
	
	if (allowTx) {
        //Antes de realizar uma transmissão vamos verificar se um intervalo de Janela já está fechado
		if(isWindowReached() && SELF_MAC_ADDRESS != 0){
			// Se já estiver, vamos calcular o novo valor da taxaMAC e informa-lo para a camada de aplicação.
			evaluateTaxaMAC();
			// após isso inicia-se um novo intervalo (ou uma nova janela)
		}


		if (currentPacket->getMac802154PacketType() == MAC_802154_DATA_PACKET) {
			if (macState == MAC_STATE_CAP) collectOutput("pkt TX state breakdown", "Contention");
			else collectOutput("pkt TX state breakdown", "Contention-free");
		}

        //Count the transmissions for taxaMAC rate, only if the packet is a DATA_PACKET
        countPacketTransmission();

		//decrement retry counter, set transmission end timer and modify mac and radio states.
		currentPacketRetries--;

		trace() << "Transmitting [" << currentPacket->getName() << "] now, remaining attempts " 
				<< currentPacketRetries << "    PacketType    " << currentPacket->getMac802154PacketType() ;

		setTimer(currentPacketResponse > 0 ? ACK_TIMEOUT : ATTEMPT_TX, txTime);
		toRadioLayer(currentPacket->dup());
		toRadioLayer(createRadioCommand(SET_STATE, TX));
	} else {
		//transmission not allowed
		trace() << "txTime " << txTime << " CAP:" << (currentFrameStart + CAPend - getClock()) << 
				" GTS:" << (currentFrameStart + GTSend - getClock());
		trace() << "Transmission of [" << currentPacket->getName() << "] stopped, not enough time";
	}
}


/**
 * TAXAMAC's functions
 */
void CrossLayerMAC802154::handleTaxaMAC(float taxaMAC)
{
    trace() << "TaxaMAC    " << taxaMAC;
}

void CrossLayerMAC802154::countPacketTransmission()
{
    currentPacketCount += 1;
    trace() << "CountingPacketTransmission    " << currentPacketCount;
}

int CrossLayerMAC802154::getCurrentPacketCount()
{
    return currentPacketCount;
}

void CrossLayerMAC802154::resetCurrentPacketCount()
{
    totalMACPacketsTransmitted += currentPacketCount;
    currentPacketCount = 0;
}

void CrossLayerMAC802154::setAckResult(int result)
{
    int previousAckCount = currentAckCount;

    if(result == 0){
        currentAckCount += 0;
    }else if(result == 1){
        currentAckCount += 1;
    } else {
        currentAckCount += 1;
    }

    trace() << "CurrentACKCount    " << currentAckCount << "    PreviousACKCount    " << previousAckCount ; 
}

int CrossLayerMAC802154::getCurrentAckCount()
{
    return currentAckCount;
}

void CrossLayerMAC802154::resetCurrentAckCount()
{
    totalMACAcksReceived += currentAckCount;
    currentAckCount = 0;
}

void CrossLayerMAC802154::countTaxaMACRecord()
{
    sequenceRecordedTaxaMAC += 1;
}

void CrossLayerMAC802154::evaluateTaxaMAC()
{
    int totalAck = getCurrentAckCount();
    int totalPackets = getCurrentPacketCount();

    float taxaMAC = (float) totalAck/totalPackets;
    taxaMAC *= 100;

    handleTaxaMAC(taxaMAC);

    resetCurrentAckCount();
    resetCurrentPacketCount();
    countTaxaMACRecord();
}

bool CrossLayerMAC802154::isWindowReached()
{
    return getCurrentPacketCount() == window;
}
