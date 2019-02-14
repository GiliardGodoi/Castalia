#include <random>
#include <iostream>

#include "TPCStrategy.h"

class TPCDistUniforme: public TPCStrategy
{
    protected:
        int maxRange;
        std::random_device rd;
        typedef std::mt19937 Generator;
        Generator gen;
        std::uniform_int_distribution<int> dis;

        int arrayPowerTx[5] = {-25, -20, -15, -12, -10};

    public:
        TPCDistUniforme();
        TPCDistUniforme(int);
        ~TPCDistUniforme();

        virtual int defineTransmissionPower(cMessage * msg);

};