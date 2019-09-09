#ifndef _F247_SIG_GEN_DUAL_COS_CPP_
#define _F247_SIG_GEN_DUAL_COS_CPP_



#include "f247_sig_gen_dual.cpp"



#define F247_PREV     F247_SIG_GEN_DUAL
#define F247_THIS     F247_SIG_GEN_DUAL_COS



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_=""); //must be implemented
    virtual ~F247_THIS();              //must be implemented
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  public:
    virtual F247_ACT_STATUS UpdateOutputs(void* arg);
  public:
    F247_SIG_INPUT LRphase;
    };



#if __INCLUDE_LEVEL__ == 0



#include <math.h>



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_), LRphase()
    {
    Log_Cons();
    LRphase.AppendMe(&inputs);
    peakL.val=1.0;
    peakR.val=1.0;
    LRphase.val=0.0;
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    }



F247_ACT_STATUS F247_THIS::UpdateOutputs(void* arg)
    {
    double T;
    if(signal_period_num && signal_period_den)
        {
        T=(2.0*M_PI)*((double)sample_number*((double)signal_period_den/(double)signal_period_num));
        valL.val=peakL.val*cos(T-(0.5*LRphase.val));
        valR.val=peakR.val*cos(T+(0.5*LRphase.val));
        }
      else
        {
        valL.val=peakL.val*( (sample_number&1));
        valR.val=peakR.val*(!(sample_number&1));
        }
    return F247_ACT_STATUS_Done;
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_SIG_GEN_DUAL_COS_CPP_

