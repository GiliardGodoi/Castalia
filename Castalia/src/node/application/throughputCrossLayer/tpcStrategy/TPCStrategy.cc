#include "TPCStrategy.h"


TPCStrategy::TPCStrategy(){
    currentPower = -10;
}

TPCStrategy::TPCStrategy(int power){
    currentPower = power;
}

TPCStrategy::~TPCStrategy(){}


int TPCStrategy::defineTransmissionPower(cMessage * msg)
{
    return currentPower;
}