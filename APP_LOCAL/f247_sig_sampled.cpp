#ifndef _F247_SIG_SAMPLED_CPP_
#define _F247_SIG_SAMPLED_CPP_



#include "f247_sig.cpp"



typedef unsigned int F247_SIG_TIME; //time axis



//#define F247_SIG_TIME_MAX      UINT_MAX
//#define F247_SIG_TIME_MAX_SQRT (sqrt(UINT_MAX))



#define F247_PREV   F247_SIG
#define F247_THIS   F247_SIG_SAMPLED



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_=""); //must be implemented
    virtual ~F247_THIS();              //must be implemented
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  public:
    virtual F247_ACT_STATUS UpdateTime(void* arg)
        {
        //sample_number++;
        return F247_ACT_STATUS_Done;
        };
    virtual void ResetTime(void)
        {
        sample_number=0;
        };
  public:
    F247_SIG_TIME sample_number;
    };



#if __INCLUDE_LEVEL__ == 0



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_)
    {
    Log_Cons();
    ResetTime();
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_SIG_SAMPLED_CPP_

