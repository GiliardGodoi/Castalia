#include "TPCUniforme.h"

TPCDistUniforme::TPCDistUniforme()
{
    TPCDistUniforme(4);
};

TPCDistUniforme::TPCDistUniforme(int max) : maxRange(max), gen(rd()), dis(std::uniform_int_distribution<>(0,maxRange))
{ };


TPCDistUniforme::~TPCDistUniforme()
{ };


int TPCDistUniforme::defineTransmissionPower(cMessage * msg)
{
    ThroughputCrossLayerMsg *cmd = check_and_cast <ThroughputCrossLayerMsg*>(msg);
    int msgType = cmd->getType();
    double taxaMAC = cmd->getParameter();

    
    int indice = dis(gen);
    int power = arrayPowerTx[indice];

    return power;
};