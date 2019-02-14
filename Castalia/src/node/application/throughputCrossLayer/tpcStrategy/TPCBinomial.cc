
#include "TPCBinomial.h"


TPCBinomial::TPCBinomial() : binomialTries(4), probability(0.5)
{
    TPCBinomial(binomialTries, probability);
};

TPCBinomial::TPCBinomial(int N,double P) : binomialTries(N), probability(P), gen(rd()), dis(std::binomial_distribution<>(binomialTries,probability))
{ };

TPCBinomial::~TPCBinomial()
{

};

int TPCBinomial::defineTransmissionPower(cMessage * msg)
{
    int indice = dis(gen);
    int power = arrayPowerTx[indice];

    return power;
}