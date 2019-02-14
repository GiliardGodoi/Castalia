#ifndef _THROUGHPUT_CROSS_LAYER_H_
#define _THROUGHPUT_CROSS_LAYER_H_

#include <map>
#include "VirtualApplication.h"
#include "ThroughputCrossLayerMsg_m.h"

#include "./tpcStrategy/TPCStrategy.h"
#include "./tpcStrategy/TPCBinomial.h"
#include "./tpcStrategy/TPCUniforme.h"

using namespace std;

enum ThroughputCrossLayerTimers {
    SEND_PACKET = 1
};

enum TPCStrategiesID {
    TPC_DEFAULT = 0,
    TPC_BINOMIAL = 1,
    TPC_UNIFORME = 2,
};

class ThroughputCrossLayer: public VirtualApplication {
    protected:
        double packet_rate;
        double startupDelay;
        double delayLimit;
        float packet_spacing;
        int dataSN;
        int recipientId;
        string recipientAddress;

        //variables below are used to determine the packet delivery rates.	
        int numNodes;
        map<long,int> packetsReceived;
        map<long,int> bytesReceived;
        map<long,int> packetsSent;

        void startup();
        void fromNetworkLayer(ApplicationPacket *, const char *, double, double);
        void timerFiredCallback(int);
        void finishSpecific();

        void handleRadioControlMessage(RadioControlMessage *);
        int handleControlCommand(cMessage * msg);


        /* Transmission Power Control Strategies 

            Variables and methods below are used to Transmission Power Control algorithms
            The different strategies are implemented with design patterns' Strategy
        */
        TPCStrategy * TPC;
        int strategyID; // 
        double probability; //for Binomial Distribution TPC
        int defaultPowerTransmission;
        int currentPowerTx;
        
    public:
        int getPacketsSent(int addr) { return packetsSent[addr]; }
        int getPacketsReceived(int addr) { return packetsReceived[addr]; }
        int getBytesReceived(int addr) { return bytesReceived[addr]; }

};

#endif