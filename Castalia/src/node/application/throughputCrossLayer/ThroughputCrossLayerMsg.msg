enum ThroughputCrossLayerMsgCommandDef 
{
    TAXA_MAC_RATE = 111;
    BUFFER_RATE = 222;
}

message ThroughputCrossLayerMsg 
{
    int type enum (ThroughputCrossLayerMsgCommandDef);
    double parameter;
}