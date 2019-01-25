
package node.communication.mac.mac802154.crossLayerMAC802154;

simple CrossLayerMAC802154 extends node.communication.mac.mac802154.Basic802154 {
    parameters:
        int window = default(5);
        int currentAckCount = default(0);
        int currentPacketCount = default(0);
        int sequenceRecordedTaxaMAC = default(0);

        int totalMACPacketsTransmitted = default(0);
        int totalMACAcksReceived = default(0);
        
        @class(CrossLayerMAC802154);
}