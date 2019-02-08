#ifndef _THROUGHPUT_CROSS_LAYER_H_
#define _THROUGHPUT_CROSS_LAYER_H_

#include <map>
#include "VirtualApplication.h"
#include "ThroughputCrossLayerMsg_m.h"

#include "./tpcStrategy/TPCBinomial.h"

using namespace std;

enum ThroughputCrossLayerTimers {
    SEND_PACKET = 1
};

class ThroughputCrossLayer: public VirtualApplication {
    private:
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

        TPCStrategy transmissionPowerControl;

    protected:
        int currentPowerTx;

        void startup();
        void fromNetworkLayer(ApplicationPacket *, const char *, double, double);
        void timerFiredCallback(int);
        void finishSpecific();

        void handleRadioControlMessage(RadioControlMessage *);
        int handleControlCommand(cMessage * msg);

    public:
        int getPacketsSent(int addr) { return packetsSent[addr]; }
        int getPacketsReceived(int addr) { return packetsReceived[addr]; }
        int getBytesReceived(int addr) { return bytesReceived[addr]; }

};

#endif