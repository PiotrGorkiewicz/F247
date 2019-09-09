#ifndef _F247_BRANCHED_CPP_
#define _F247_BRANCHED_CPP_



#include "f247_reportable.cpp"
#include "f247_runnable.cpp"
#include <stdlib.h>



#define F247_PREV          F247_REPORTABLE
#define F247_THIS          F247_BRANCHED



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_="");
    virtual ~F247_THIS();
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  public:
    virtual void AttachRunnable(F247_RUNNABLE* p);
    virtual void AttachPeerAtEnd(F247_THIS* p);
    virtual void AttachMinorAtEnd(F247_THIS* p);
    /*
    template <class TT> F247_THIS* FindTypeUpwards(void)
        {
        if(NULL==major)
            return NULL;
        if(NULL!=dynamic_cast<TT*>(major))
            return major;
        return major->FindTypeUpwards<TT>();
        }
    template <class TT> F247_THIS* FindTypeDownwards(void)
        {
        F247_THIS* p,q;
        p=minor;
        while(NULL!=p)
            {
            if(NULL!=dynamic_cast<TT*>(p))
                return p;
            p=p->peerR;
            }
        p=minor;
        while(NULL!=p)
            {
            if(NULL!=(q=p->FindTypeDownwards<TT>()))
                return q;
            p=p->peerR;
            }
        return p;
        }
    */
    friend class F247_ACT_ACTION;
    virtual void RunDownwards   (F247_ACT_ACTION* action, void* arg);
    virtual void DiveRunUpwards (F247_ACT_ACTION* action, void* arg);
    virtual void ResetResults   ();
  protected:
    F247_THIS* major;
    F247_THIS* peerR;
    F247_THIS* minor;
    F247_THIS* peerL(); //not stored; find it if needed
    F247_RUNNABLE* runnable;
  public:
    F247_ACT_STATUS result;
    };



#if __INCLUDE_LEVEL__ == 0



F247_THIS* F247_THIS::peerL()
    {
    F247_THIS* p=NULL;
    if(NULL!=major)
        {
        p=major->minor;
        while(1)
            {
            if(NULL==p)
                break; // peerL is unreachable due to absence of major or internal error occured
            if(this==p)
                {
                p=NULL;
                break; // no peerL; I am the first
                }
            if(this==p->peerR)
                break; // found
            p=p->peerR;
            }
        }
    return p;
    }



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_)
    {
    Log_Cons();
    major=NULL;
    peerR=NULL;
    minor=NULL;
    runnable=NULL;
    result=F247_ACT_STATUS_Reset;
    }



F247_THIS::~F247_THIS()
    {
    if(NULL!=peerL())
        {
        if(NULL!=peerR)
            peerL()->peerR=peerR; //replace me
          else
            peerL()->peerR=NULL; //blind my place
        }
      else
        {
        if(NULL!=major)
            {
            if(this==major->minor)
                major->minor=peerR;
            }
        }
    Log_Dest();
    }



void F247_THIS::AttachRunnable(F247_RUNNABLE* p)
    {
    runnable=p;
    }



void F247_THIS::AttachPeerAtEnd(F247_THIS* p)
    {
    if(NULL!=peerR)
        peerR->AttachPeerAtEnd(p);
      else
        {
        peerR=p;
        peerR->major=major;
        }
    }



void F247_THIS::AttachMinorAtEnd(F247_THIS* p)
    {
    if(NULL!=minor)
        minor->AttachPeerAtEnd(p);
      else
        {
        minor=p;
        minor->major=this;
        }
    }



void F247_THIS::ResetResults()
    {
    result=F247_ACT_STATUS_Reset;
    if(NULL!=peerR)
        peerR->ResetResults();
    if(NULL!=minor)
        minor->ResetResults();
    }



void F247_THIS::RunDownwards(F247_ACT_ACTION* action, void* arg)
    {
    if(NULL!=action)
        {
        if(NULL!=runnable)
            result=action->Action(runnable,arg);
        if(NULL!=peerR)
            peerR->RunDownwards(action,arg);
        if(NULL!=minor)
            minor->RunDownwards(action,arg);
        }
    }



void F247_THIS::DiveRunUpwards(F247_ACT_ACTION* action, void* arg)
    {
    if(NULL!=action)
        {
        if(NULL!=minor)
            minor->DiveRunUpwards(action,arg);
        if(NULL!=peerR)
            peerR->DiveRunUpwards(action,arg);
        if(NULL!=runnable)
            result=action->Action(runnable,arg);
        }
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_BRANCHED_CPP_

