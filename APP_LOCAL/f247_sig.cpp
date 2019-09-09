#ifndef _F247_SIG_CPP_
#define _F247_SIG_CPP_



#include "f247_simple_types.cpp"

#include "f247_allocatable.cpp"



typedef double F247_SIG_VAL; //value



#define F247_PREV   F247_ALLOCATABLE
#define F247_THIS   F247_SIG



//Each time period the following steps must pass for the whole SIG network:
class F247_ACT_SIG_INP;  // 1.SampleInputs
class F247_ACT_SIG_OUT;  // 2.UpdateOutputs
class F247_ACT_SIG_CLK;  // 3.UpdateTime



class F247_SIG_OUTPUT;
class F247_SIG_OUTPUT
    {
  public:
    F247_SIG_VAL      val;
    F247_SIG_OUTPUT*  next;
    F247_SIG_OUTPUT() { val=0.0; next=NULL; }
    void AppendMe(F247_SIG_OUTPUT** lptr) { while(*lptr!=NULL) lptr=&((*lptr)->next); *lptr=this; }
    };



class F247_SIG_INPUT;
class F247_SIG_INPUT
    {
  public:
    F247_SIG_OUTPUT* src;
    F247_SIG_VAL     val;
    F247_SIG_INPUT*  next;
    F247_SIG_INPUT() { val=0.0; next=NULL; src=NULL; };
    void AppendMe(F247_SIG_INPUT** lptr) { while(*lptr!=NULL) lptr=&((*lptr)->next); *lptr=this; };
    void Disconnect() { src=NULL; };
    void Connect (F247_SIG_OUTPUT* srrc) { src=srrc; };
    void Sample () { if(NULL!=src) val=src->val; };
    };



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_=""); //must be implemented
    virtual ~F247_THIS();              //must be implemented
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  public:
    friend class F247_ACT_SIG_INP;
    friend class F247_ACT_SIG_OUT;
    friend class F247_ACT_SIG_CLK;
  public:
    static F247_ACT_SIG_INP act_sig_inp;
    static F247_ACT_SIG_OUT act_sig_out;
    static F247_ACT_SIG_CLK act_sig_clk;
  public:
    F247_SIG_INPUT*  inputs;
    F247_SIG_OUTPUT* outputs;
  public:
    virtual F247_ACT_STATUS SampleInputs(void* arg)
        {
        F247_SIG_INPUT* ptr=inputs;
        while(NULL!=ptr)
            {
            ptr->Sample();
            ptr=ptr->next;
            }
        return F247_ACT_STATUS_Done;
        };
    virtual F247_ACT_STATUS UpdateOutputs(void* arg) {return F247_ACT_STATUS_Skipped;};
    virtual F247_ACT_STATUS UpdateTime(void* arg)    {return F247_ACT_STATUS_Skipped;};
    };



class F247_ACT_SIG_INP : public F247_ACT_ACTION
    {
  public:
    virtual F247_ACT_STATUS Action(F247_RUNNABLE* r, void* arg);
    };



class F247_ACT_SIG_OUT : public F247_ACT_ACTION
    {
  public:
    virtual F247_ACT_STATUS Action(F247_RUNNABLE* r, void* arg);
    };



class F247_ACT_SIG_CLK : public F247_ACT_ACTION
    {
  public:
    virtual F247_ACT_STATUS Action(F247_RUNNABLE* r, void* arg);
    };



#if __INCLUDE_LEVEL__ == 0



F247_ACT_SIG_INP   F247_THIS::act_sig_inp; //static

F247_ACT_SIG_OUT   F247_THIS::act_sig_out; //static

F247_ACT_SIG_CLK   F247_THIS::act_sig_clk; //static



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_)
    {
    Log_Cons();
    inputs =NULL;
    outputs=NULL;
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    }



F247_ACT_STATUS F247_ACT_SIG_INP::Action(F247_RUNNABLE* r, void* arg)
    {
    F247_SIG* _r;
    if(NULL!=(_r=dynamic_cast<F247_SIG*>(r)))
        return _r->SampleInputs(arg);
    return F247_ACT_STATUS_SkippedType;
    }



F247_ACT_STATUS F247_ACT_SIG_OUT::Action(F247_RUNNABLE* r, void* arg)
    {
    F247_SIG* _r;
    if(NULL!=(_r=dynamic_cast<F247_SIG*>(r)))
        return _r->UpdateOutputs(arg);
    return F247_ACT_STATUS_SkippedType;
    }



F247_ACT_STATUS F247_ACT_SIG_CLK::Action(F247_RUNNABLE* r, void* arg)
    {
    F247_SIG* _r;
    if(NULL!=(_r=dynamic_cast<F247_SIG*>(r)))
        return _r->UpdateTime(arg);
    return F247_ACT_STATUS_SkippedType;
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_SIG_CPP_

