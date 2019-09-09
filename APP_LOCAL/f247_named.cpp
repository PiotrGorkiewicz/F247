#ifndef   _F247_NAMED_CPP_
#define   _F247_NAMED_CPP_



#include "f247_defs1.cpp"



typedef unsigned int F247_ID;



//typedef void (*F247_HANDLER_f)(void*);



#define F247_PREV  F247_NAMED
#define F247_THIS  F247_NAMED

#define F247_ROOT  F247_NAMED



class F247_THIS
    {
  public:
    F247_THIS(const char* id_str_="");
    virtual ~F247_THIS();
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  private:
    static F247_ID source;
  protected:
    F247_ID     id;
    const char* id_str;
    };



#if __INCLUDE_LEVEL__ == 0



F247_ID F247_THIS::source=0;



F247_THIS::F247_THIS(const char* id_str_)
    {
    id=++source;
    id_str=id_str_;
    }



F247_THIS::~F247_THIS()
    {
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif  //_F247_NAMED_CPP_

