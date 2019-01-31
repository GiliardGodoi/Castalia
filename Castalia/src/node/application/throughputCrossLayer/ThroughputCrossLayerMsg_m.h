//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/application/throughputCrossLayer/ThroughputCrossLayerMsg.msg.
//

#ifndef _THROUGHPUTCROSSLAYERMSG_M_H_
#define _THROUGHPUTCROSSLAYERMSG_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Enum generated from <tt>src/node/application/throughputCrossLayer/ThroughputCrossLayerMsg.msg:2</tt> by nedtool.
 * <pre>
 * enum ThroughputCrossLayerMsgCommandDef
 * {
 * 
 *     TAXA_MAC_RATE = 111;
 *     BUFFER_RATE = 222;
 * }
 * </pre>
 */
enum ThroughputCrossLayerMsgCommandDef {
    TAXA_MAC_RATE = 111,
    BUFFER_RATE = 222
};

/**
 * Class generated from <tt>src/node/application/throughputCrossLayer/ThroughputCrossLayerMsg.msg:8</tt> by nedtool.
 * <pre>
 * message ThroughputCrossLayerMsg
 * {
 *     int type @enum(ThroughputCrossLayerMsgCommandDef);
 *     double parameter;
 * }
 * </pre>
 */
class ThroughputCrossLayerMsg : public ::cMessage
{
  protected:
    int type_var;
    double parameter_var;

  private:
    void copy(const ThroughputCrossLayerMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ThroughputCrossLayerMsg&);

  public:
    ThroughputCrossLayerMsg(const char *name=NULL, int kind=0);
    ThroughputCrossLayerMsg(const ThroughputCrossLayerMsg& other);
    virtual ~ThroughputCrossLayerMsg();
    ThroughputCrossLayerMsg& operator=(const ThroughputCrossLayerMsg& other);
    virtual ThroughputCrossLayerMsg *dup() const {return new ThroughputCrossLayerMsg(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getType() const;
    virtual void setType(int type);
    virtual double getParameter() const;
    virtual void setParameter(double parameter);
};

inline void doPacking(cCommBuffer *b, ThroughputCrossLayerMsg& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, ThroughputCrossLayerMsg& obj) {obj.parsimUnpack(b);}


#endif // ifndef _THROUGHPUTCROSSLAYERMSG_M_H_

