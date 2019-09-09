#ifndef   _F247_EVENT_CPP_
#define   _F247_EVENT_CPP_



#include "f247_reportable.cpp"



#define F247_PREV  F247_REPORTABLE
#define F247_THIS  F247_EVENT



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_="") : F247_PREV(id_str_) {Log_Cons();};
    virtual ~F247_THIS() {Log_Dest();}
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
    };



#if __INCLUDE_LEVEL__ == 0



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif  //_F247_EVENT_CPP_

