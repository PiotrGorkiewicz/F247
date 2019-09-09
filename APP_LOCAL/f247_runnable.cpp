#ifndef _F247_RUNNABLE_CPP_
#define _F247_RUNNABLE_CPP_



#include "f247_reportable.cpp"
#include <stdlib.h>



#define F247_PREV          F247_REPORTABLE
#define F247_THIS          F247_RUNNABLE



class F247_ACT_ACTION; //each kind of action inherits from F247_ACT_ACTION



typedef enum
    {
    //-------- error --------------
    F247_ACT_STATUS_Reset=0,         //Action() not entered; possible internal error
    F247_ACT_STATUS_ErrRunTimeDep,   //error due to lack of run time dependence e.g. gui view still needs environment
    F247_ACT_STATUS_ErrResource,     //error due to lack of resources e.g. memory
    F247_ACT_STATUS_ErrFatal,        //internal error - unspecified
    F247_ACT_STATUS_ErrMAX,          //not used; only as borderline
    //-------- success ------------
    F247_ACT_STATUS_SkippedType,     //Action() entered but class not matched; skipped
    F247_ACT_STATUS_Skipped,         //ok, already done
    F247_ACT_STATUS_Done,            //ok, done now
    F247_ACT_STATUS_False,           //answer: no
    F247_ACT_STATUS_True,            //answer: yes
    F247_ACT_STATUS_MAX
    //-----------------------------
    }
    F247_ACT_STATUS;



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_="");
    virtual ~F247_THIS();
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
    friend class F247_ACT_ACTION;
    };



class F247_ACT_ACTION //each kind of action inherits from F247_ACT_ACTION
    {
  public:
    virtual F247_ACT_STATUS Action(F247_RUNNABLE* r, void* arg) {return F247_ACT_STATUS_SkippedType;}
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



#endif //_F247_RUNNABLE_CPP_



























