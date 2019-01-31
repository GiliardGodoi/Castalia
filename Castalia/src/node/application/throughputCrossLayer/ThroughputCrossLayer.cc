#include "ThroughputCrossLayer.h"

Define_Module(ThroughputCrossLayer);

void ThroughputCrossLayer::startup()
{
    /* CL startup */
    arrayPowerTx[0] = -25;
    arrayPowerTx[1] = -20;
    arrayPowerTx[2] = -15;
    arrayPowerTx[3] = -12;
    arrayPowerTx[4] = -10;

    currentPowerTx = -10;

    // default startup
   	packet_rate = par("packet_rate");
	startupDelay = par("startupDelay");
	delayLimit = par("delayLimit");
	packet_spacing = packet_rate > 0 ? 1 / float (packet_rate) : -1;
	dataSN = 0;
	recipientId = atoi(recipientAddress.c_str());
	recipientAddress = par("nextRecipient").stringValue();

	numNodes = getParentModule()->getParentModule()->par("numNodes");
	
	packetsReceived.clear();
	bytesReceived.clear();
	packetsSent.clear();
	
	if (packet_spacing > 0 && recipientAddress.compare(SELF_NETWORK_ADDRESS) != 0)
		setTimer(SEND_PACKET, packet_spacing + startupDelay);
	else
		trace() << "Not sending packets";

	declareOutput("Packets received per node"); 
}

void ThroughputCrossLayer::fromNetworkLayer(ApplicationPacket * rcvPacket,const char *source, double rssi, double lqi)
{
	int sequenceNumber = rcvPacket->getSequenceNumber();
	int sourceId = atoi(source);
	// This node is the final recipient for the packet
	if (recipientAddress.compare(SELF_NETWORK_ADDRESS) == 0) {
		if (delayLimit == 0 || (simTime() - rcvPacket->getCreationTime()) <= delayLimit) {
			trace() << "RECEIVED_PACKET_#  " << sequenceNumber << "   FROM   " << source << "    RSSI   " << rssi;
			collectOutput("Packets received per node", sourceId);
			packetsReceived[sourceId]++;
			bytesReceived[sourceId] += rcvPacket->getByteLength();
		} else {
			trace() << "Packet #" << sequenceNumber << " from node " << source <<
				" exceeded delay limit of " << delayLimit << "s";
		}
	// Packet has to be forwarded to the next hop recipient
	} else {
		ApplicationPacket* fwdPacket = rcvPacket->dup();
		// Reset the size of the packet, otherwise the app overhead will keep adding on
		fwdPacket->setByteLength(0);
//		toNetworkLayer(fwdPacket, recipientAddress.c_str());
		toNetworkLayer(fwdPacket, recipientAddress.c_str());
	}
}

void ThroughputCrossLayer::timerFiredCallback(int index)
{
    switch (index)
    {
        case SEND_PACKET:
            trace() << "Sending packet #" << dataSN;
			toNetworkLayer(createGenericDataPacket(0, dataSN), recipientAddress.c_str());
			packetsSent[recipientId]++;
			dataSN++;
			setTimer(SEND_PACKET, packet_spacing);
            break;
    }
}

void ThroughputCrossLayer::finishSpecific()
{
	declareOutput("Packets reception rate");
	declareOutput("Packets loss rate");

	cTopology *topo;	// temp variable to access packets received by other nodes
	topo = new cTopology("topo");
	topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());

	long bytesDelivered = 0;
	for (int i = 0; i < numNodes; i++) {
		ThroughputCrossLayer *appModule = dynamic_cast<ThroughputCrossLayer*>
			(topo->getNode(i)->getModule()->getSubmodule("Application"));
		if (appModule) {
			int packetsSent = appModule->getPacketsSent(self);
			if (packetsSent > 0) { // this node sent us some packets
				float rate = (float)packetsReceived[i]/packetsSent;
				collectOutput("Packets reception rate", i, "total", rate);
				collectOutput("Packets loss rate", i, "total", 1-rate);
			}

			bytesDelivered += appModule->getBytesReceived(self);
		}
	}
	delete(topo);

	if (packet_rate > 0 && bytesDelivered > 0) {
		double energy = (resMgrModule->getSpentEnergy() * 1000000000)/(bytesDelivered * 8);	//in nanojoules/bit
		declareOutput("Energy nJ/bit");
		collectOutput("Energy nJ/bit","",energy);
	}
}

void ThroughputCrossLayer::handleRadioControlMessage(RadioControlMessage * radioMsg)
{
    if(radioMsg == NULL){
        trace() << "Warning!! received a NULL radioControlMessage" ;
        return;
    }

    switch (radioMsg->getRadioControlMessageKind()) {
		case CARRIER_SENSE_INTERRUPT:
			trace() << "CS Interrupt received! current RSSI value is: " << radioModule->readRSSI();
            break;
	}

}

int ThroughputCrossLayer::handleControlCommand(cMessage * msg)
{
	ThroughputCrossLayerMsg *cmd = check_and_cast <ThroughputCrossLayerMsg*>(msg);

	int type = cmd->getType();
	
	switch(type)
	{
		case TAXA_MAC_RATE :
		{
			double taxaMAC = cmd->getParameter();
			trace() << "APP_TAXAMAC    " << taxaMAC;
			break;
		}
	}


    delete cmd;

	return 3;
}