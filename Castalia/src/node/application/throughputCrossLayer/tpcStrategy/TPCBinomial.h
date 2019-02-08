#include <random>
#include "TPCStrategy.h"

class TPCBinomial: public TPCStrategy
{
    protected:
        static random_device rd;
        static mt19937 gen;

        int arrayPowerTx[5];
    public:
        static binomial_distribution<> dis;

        TPCBinomial();
        TPCBinomial(int,double);

        int defineTransmissionPower(cMessage * msg);
};