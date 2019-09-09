#ifndef _F247_SIG_SAMPLING_CPP_
#define _F247_SIG_SAMPLING_CPP_



#include "f247_sig_sampled.cpp"

#include "f247_branched.cpp"



#define F247_PREV   F247_SIG_SAMPLED
#define F247_THIS   F247_SIG_SAMPLING



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_=""); //must be implemented
    virtual ~F247_THIS();              //must be implemented
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  public:
    virtual void ConnectUpdateTime( F247_BRANCHED* tree );
    virtual void OutUpdateTime(void);
  protected:
    F247_BRANCHED* update_time_tree=NULL;
    SATOM update_time_on=0;
  public:
    virtual void SetUpdateTimeOn(void);
    virtual void SetUpdateTimeOff(void);
    };



#if __INCLUDE_LEVEL__ == 0



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_)
    {
    Log_Cons();
    update_time_tree=NULL;
    update_time_on=0;
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    }



void F247_THIS::ConnectUpdateTime( F247_BRANCHED* tree )
    {
    update_time_tree=tree;
    }



void F247_THIS::OutUpdateTime(void)
    {
    if(NULL!=update_time_tree && update_time_on)
        {
        update_time_tree->RunDownwards(&F247_SIG_SAMPLED::act_sig_inp,NULL);
        update_time_tree->RunDownwards(&F247_SIG_SAMPLED::act_sig_out,NULL);
        update_time_tree->RunDownwards(&F247_SIG_SAMPLED::act_sig_clk,NULL);
        }
    }



void F247_THIS::SetUpdateTimeOn(void)
    {
    update_time_on=1;
    };



void F247_THIS::SetUpdateTimeOff(void)
    {
    update_time_on=0;
    };



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_SIG_SAMPLING_CPP_

