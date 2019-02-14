#ifndef _TPC_STRATEGY_H
#define _TPC_STRATEGY_H

#include <omnetpp.h>
#include "ThroughputCrossLayerMsg_m.h"

class TPCStrategy 
{
    protected:
        int currentPower;
    public:
        TPCStrategy();
        TPCStrategy(int);
        ~TPCStrategy();

        virtual int defineTransmissionPower(cMessage * msg);
};

#endif
