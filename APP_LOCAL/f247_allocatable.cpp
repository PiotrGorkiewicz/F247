#ifndef _F247_ALLOCATABLE_CPP_
#define _F247_ALLOCATABLE_CPP_



#include "f247_runnable.cpp"



#define F247_PREV             F247_RUNNABLE
#define F247_THIS             F247_ALLOCATABLE



class F247_ACT_ALLOCATE;
class F247_ACT_REALLOCATE;
class F247_ACT_FREE;
class F247_ACT_IS_ALLOCATED;



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_="");
    virtual ~F247_THIS();
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
    //virtual F247_ROOT* ProximateAncestor(void) {return (F247_PREV*)this;} //must be copied
  public:
    friend class F247_ACT_ALLOCATE;
    friend class F247_ACT_REALLOCATE;
    friend class F247_ACT_FREE;
    friend class F247_ACT_IS_ALLOCATED;
  public:
    static F247_ACT_ALLOCATE     act_allocate;
    static F247_ACT_REALLOCATE   act_reallocate;
    static F247_ACT_FREE         act_free;
    static F247_ACT_IS_ALLOCATED act_is_allocated;
  public:
    virtual F247_ACT_STATUS Allocate(void* arg);
    virtual F247_ACT_STATUS Reallocate(void* arg);
    virtual F247_ACT_STATUS Free(void* arg);
    virtual F247_ACT_STATUS IsAllocated(void* arg);
  protected:
    unsigned int to_allocate=99;
    };



class F247_ACT_ALLOCATE : public F247_ACT_ACTION
    {
  public:
    virtual F247_ACT_STATUS Action(F247_RUNNABLE* r, void* arg);
    };



class F247_ACT_REALLOCATE : public F247_ACT_ACTION
    {
  public:
    virtual F247_ACT_STATUS Action(F247_RUNNABLE* r, void* arg);
    };



class F247_ACT_FREE : public F247_ACT_ACTION
    {
  public:
    virtual F247_ACT_STATUS Action(F247_RUNNABLE* r, void* arg);
    };



class F247_ACT_IS_ALLOCATED : public F247_ACT_ACTION
    {
  public:
    virtual F247_ACT_STATUS Action(F247_RUNNABLE* r, void* arg);
    };



#if __INCLUDE_LEVEL__ == 0



F247_ACT_ALLOCATE     F247_THIS::act_allocate; //static

F247_ACT_REALLOCATE   F247_THIS::act_reallocate; //static

F247_ACT_FREE         F247_THIS::act_free; //static

F247_ACT_IS_ALLOCATED F247_THIS::act_is_allocated; //static




F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_)
    {
    to_allocate=0;
    Log_Cons();
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    Free(NULL);
    }



F247_ACT_STATUS F247_THIS::Allocate(void* arg)
    {
    return F247_ACT_STATUS_SkippedType;
    }



F247_ACT_STATUS F247_THIS::Free(void* arg)
    {
    return F247_ACT_STATUS_SkippedType;
    }



F247_ACT_STATUS F247_THIS::Reallocate(void* arg)
    {
    F247_ACT_STATUS res;
    res=Free(arg);
    if( (F247_ACT_STATUS_Done==res) || (F247_ACT_STATUS_Skipped==res) )
        res=Allocate(arg);
    return res;
    }



F247_ACT_STATUS F247_THIS::IsAllocated(void* arg)
    {
    return to_allocate ? F247_ACT_STATUS_False : F247_ACT_STATUS_True;
    }



F247_ACT_STATUS F247_ACT_ALLOCATE::Action(F247_RUNNABLE* r, void* arg)
    {
    F247_ALLOCATABLE* _r;
    if(NULL!=(_r=dynamic_cast<F247_ALLOCATABLE*>(r)))
        return _r->Allocate(arg);
    return F247_ACT_STATUS_SkippedType;
    }



F247_ACT_STATUS F247_ACT_REALLOCATE::Action(F247_RUNNABLE* r, void* arg)
    {
    F247_ALLOCATABLE* _r;
    if(NULL!=(_r=dynamic_cast<F247_ALLOCATABLE*>(r)))
        return _r->Reallocate(arg);
    return F247_ACT_STATUS_SkippedType;
    }



F247_ACT_STATUS F247_ACT_FREE::Action(F247_RUNNABLE* r, void* arg)
    {
    F247_ALLOCATABLE* _r;
    if(NULL!=(_r=dynamic_cast<F247_ALLOCATABLE*>(r)))
        return _r->Free(arg);
    return F247_ACT_STATUS_SkippedType;
    }



F247_ACT_STATUS F247_ACT_IS_ALLOCATED::Action(F247_RUNNABLE* r, void* arg)
    {
    F247_ALLOCATABLE* _r;
    if(NULL!=(_r=dynamic_cast<F247_ALLOCATABLE*>(r)))
        return _r->IsAllocated(arg);
    return F247_ACT_STATUS_SkippedType;
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_ALLOCATABLE_CPP_

