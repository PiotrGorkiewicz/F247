#ifndef   _F247_REPORTABLE_CPP_
#define   _F247_REPORTABLE_CPP_



#include "f247_named.cpp"



#define F247_PREV  F247_ROOT
#define F247_THIS  F247_REPORTABLE



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_="");
    virtual ~F247_THIS();
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  protected:
    void Log_Cons(void);
    void Log_Dest(void);
    };



#if __INCLUDE_LEVEL__ == 0



#include <stdio.h>
#include <assert.h>
//#define NDEBUG //uncomment it to turn off assert



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_)
    {
    Log_Cons();
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    }



void F247_THIS::Log_Cons(void)
    {
    fprintf(stderr,"ID=%u TYPE=%s Cons ID_STR=%s\n",id,TypeName(),id_str);
    }



void F247_THIS::Log_Dest(void)
    {
    fprintf(stderr,"ID=%u TYPE=%s Destr ID_STR=%s\n",id,TypeName(),id_str);
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif  //_F247_REPORTABLE_CPP_

