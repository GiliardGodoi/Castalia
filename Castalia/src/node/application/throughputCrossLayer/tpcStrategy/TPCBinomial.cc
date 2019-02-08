#include "TPCBinomial.h"

random_device TPCBinomial::rd;
mt19937 TPCBinomial::gen(TPCBinomial::rd());
binomial_distribution<> TPCBinomial::dis(4, 0.7);

TPCBinomial::TPCBinomial(){
    arrayPowerTx[0] = -25;
    arrayPowerTx[1] = -20;
    arrayPowerTx[2] = -15;
    arrayPowerTx[3] = -12;
    arrayPowerTx[4] = -10;
}

TPCBinomial::TPCBinomial(int N,double P){

    arrayPowerTx[0] = -25;
    arrayPowerTx[1] = -20;
    arrayPowerTx[2] = -15;
    arrayPowerTx[3] = -12;
    arrayPowerTx[4] = -10;
};

int TPCBinomial::defineTransmissionPower(cMessage * msg)
{
    return 0;
}