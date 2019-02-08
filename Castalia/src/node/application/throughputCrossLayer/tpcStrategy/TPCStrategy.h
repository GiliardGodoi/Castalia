#include <omnetpp.h>
#include "CastaliaModule.h"

using namespace std;

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