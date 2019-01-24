
#include "CrossLayerMAC802154.h"

Define_Module(CrossLayerMAC802154);

void CrossLayerMAC802154::startup() {

    return Basic802154::startup();
}

void CrossLayerMAC802154::timerFiredCallback(int index) {
    switch (index)
    {
        case ACK_TIMEOUT:
            /* code */
            trace() << "ACK timeout disparado ";
            break;
    
        default:
            Basic802154::timerFiredCallback(index);
    }
}

void CrossLayerMAC802154::finishSpecific() {
    
    return Basic802154::finishSpecific();
}

