#include <random>
#include <iostream>
#include "TPCStrategy.h"

class TPCBinomial: public TPCStrategy
{
    protected:
        int binomialTries;
        double probability;
        std::random_device rd;
        typedef std::mt19937 Generator;
        Generator gen;
        std::binomial_distribution<int> dis;

        int arrayPowerTx[5] = {-25, -20, -15, -12, -10};

    public:
        TPCBinomial();
        TPCBinomial(int,double);
        ~TPCBinomial();

    
        virtual int defineTransmissionPower(cMessage * msg);
};