#ifndef _F247_SIG_HWIO_CPP_
#define _F247_SIG_HWIO_CPP_



#include "f247_sig_sampling.cpp"



#define F247_PREV   F247_SIG_SAMPLING
#define F247_THIS   F247_SIG_HWIO



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_=""); //must be implemented
    virtual ~F247_THIS();              //must be implemented
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
    };



#if __INCLUDE_LEVEL__ == 0



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_)
    {
    Log_Cons();
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_SIG_HWIO_CPP_

