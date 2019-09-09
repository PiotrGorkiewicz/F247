#ifndef _F247_SIG_PERIODIC_CPP_
#define _F247_SIG_PERIODIC_CPP_



#include "f247_sig_sampled.cpp"



#define F247_PREV   F247_SIG_SAMPLED
#define F247_THIS   F247_SIG_PERIODIC



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_=""); //must be implemented
    virtual ~F247_THIS();              //must be implemented
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  public:
    virtual void TrimTime(void);
  public:
    virtual F247_ACT_STATUS UpdateTime(void* arg);
  public:
    F247_SIG_INPUT sampling_frequency;
    F247_SIG_INPUT signal_frequency;
  public: //na chwile
  //protected:
    F247_SIG_TIME signal_period_num;
    F247_SIG_TIME signal_period_den;
    };



#if __INCLUDE_LEVEL__ == 0



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_),
    sampling_frequency(),
    signal_frequency()
    {
    Log_Cons();
    signal_period_num=1;
    signal_period_den=1;
    sampling_frequency.AppendMe(&inputs);
    signal_frequency.AppendMe(&inputs);
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    }



void F247_THIS::TrimTime(void)
    {
    if(signal_period_num)
        sample_number %= signal_period_num;
    }



F247_ACT_STATUS F247_THIS::UpdateTime(void* arg)
    {
    sample_number++;
    TrimTime();
    if(0==sample_number)
        {
        if( (sampling_frequency.src != NULL) && (signal_frequency.src != NULL) )
            {
            if( (sampling_frequency.val != 0.0) && (signal_frequency.val != 0.0) )
                {
                while(1)
                    {
                    signal_period_den=signal_frequency.val;
                    signal_period_num=sampling_frequency.val;
                    break; //idea is to improve accuracy the iteration way
                    }
                }
              else
                {
                signal_period_den=1; //very defensive
                signal_period_num=1; //very defensive
                }
            }
        }
    return F247_ACT_STATUS_Done;
    };



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_SIG_PERIODIC_CPP_

