#ifndef CROSS_LAYER_MAC_802154_H
#define CROSS_LAYER_MAC_802154_H

#include <string>
#include <vector>

#include "Basic802154.h"
#include "Basic802154Packet_m.h"

class CrossLayerMAC802154: public Basic802154 {

    protected:

    /*
    * Por enquanto não vamos sobrescrever este método aqui 
        void transmitPacket(Basic802154Packet *pkt, int retries = 0, bool GTSonly = false, double delay = 0);
    */

    	/*--- Virtual interface functions can be overwritten by a decision module ---*/
	    virtual void startup();
	    virtual void timerFiredCallback(int);
	    virtual void finishSpecific();
        
        /*--- General desicions ---*/
	    //virtual bool acceptNewPacket(Basic802154Packet *);
	    //virtual void transmissionOutcome(Basic802154Packet *, bool, string);
};

#endif // CROSS_LAYER_MAC_802154_H