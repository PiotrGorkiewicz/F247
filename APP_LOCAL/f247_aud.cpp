#ifndef _F247_AUD_CPP_
#define _F247_AUD_CPP_



#include "f247_simple_types.cpp"
#include "f247_sig_hwio.cpp"



//for device
typedef U16 F247_AUD_VAL;



#define F247_PREV             F247_SIG_HWIO
#define F247_THIS             F247_AUD



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_="");
    virtual ~F247_THIS();
  public:
    virtual void SetParams(int _argc, char** _argv);
    virtual void Break(void);
    virtual F247_SIG_TIME GetPosition(void);
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  public:
    virtual F247_ACT_STATUS Allocate(void* arg);
    virtual F247_ACT_STATUS Free(void* arg);
  protected:
    F247_SIG_TIME samp_per_sec;
    F247_SIG_TIME samp_per_period;
  protected:
    int argc;
    char** argv;
    };



#if __INCLUDE_LEVEL__ == 0



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_)
    {
    samp_per_sec=0;
    samp_per_period=0;
    argc=0;
    argv=NULL;
    Log_Cons();
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    }



F247_ACT_STATUS F247_THIS::Allocate(void* arg)
    {
    return F247_ACT_STATUS_Skipped;
    }



F247_ACT_STATUS F247_THIS::Free(void* arg)
    {
    return F247_ACT_STATUS_Skipped;
    }



void F247_THIS::SetParams(int _argc, char** _argv)
    {
    argc=_argc;
    argv=_argv;
    }



void F247_THIS::Break(void)
    {
    }



F247_SIG_TIME F247_THIS::GetPosition(void)
    {
    return 0;
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_AUD_CPP_

