#ifndef   _F247_SCALAR_TIME_CPP_
#define   _F247_SCALAR_TIME_CPP_

#include "f247_simple_types.cpp"

class F247_TIME1
    {
  protected:
    S32 seconds; //seconds from epoch; signed
    U32 x8; //tens of nanoseconds (unsigned; always increases absolute value) mixed with uncertainty
  public:
    void SetN9(S64 n9, S32 uncertainty_log10);
    void SetN8(S64 n8, S32 uncertainty_log10);
    void SetN6(S64 n6, S32 uncertainty_log10);
    void SetN3(S64 n3, S32 uncertainty_log10);
    void SetS9(S32 secs, S32 f9, S32 uncertainty_log10); //to store -1.5s: secs=-1, f9=-500000000
    void SetS8(S32 secs, S32 f8, S32 uncertainty_log10); //to store -1.5s: secs=-1, f9=-50000000
    void SetS6(S32 secs, S32 f6, S32 uncertainty_log10); //to store -1.5s: secs=-1, f9=-500000
    void SetS3(S32 secs, S32 f3, S32 uncertainty_log10); //to store -1.5s: secs=-1, f9=-500
    S32 GetUncertaintyLog10(void);
    S32 GetSeconds(void);
    S32 GetSecondF9(void);
    S32 GetSecondF8(void);
    S32 GetSecondF6(void);
    S32 GetSecondF3(void);
    };

#if __INCLUDE_LEVEL__ == 0

#include <assert.h>
//#define NDEBUG //uncomment it to turn off assert
#define ASSERT(x) assert(x)

void F247_TIME1::SetN9(S64 n9, S32 uncertainty_log10)
    {
    ASSERT( uncertainty_log10 >= -15 && uncertainty_log10 <= 15);
    seconds=n9/1000000000LL;
    n9-=(1000000000LL*seconds);
    ASSERT( n9 == (1000000000LL*seconds) );
    if(0>n9)
        x8=n9/-10; //TODO: some round?
      else
        x8=n9/ 10; //TODO: some round?
    ASSERT( 0 == (x8 & 0xF8000000) );
    uncertainty_log10 *= (1L<<27); //shift it upwards keeping the sign
    x8 |= (U32)(uncertainty_log10);
    };

void F247_TIME1::SetN8(S64 n8, S32 uncertainty_log10)
    {
    ASSERT( uncertainty_log10 >= -15 && uncertainty_log10 <= 15);
    seconds=n8/100000000LL;
    n8-=(100000000LL*seconds);
    ASSERT( n8 == (100000000LL*seconds) );
    if(0>n8)
        x8=-n8;
      else
        x8= n8;
    ASSERT( 0 == (x8 & 0xF8000000) );
    uncertainty_log10 *= (1L<<27); //shift it upwards keeping the sign
    x8 |= (U32)(uncertainty_log10);
    };

void F247_TIME1::SetN6(S64 n6, S32 uncertainty_log10)
    {
    ASSERT( uncertainty_log10 >= -15 && uncertainty_log10 <= 15);
    seconds=n6/1000000LL;
    n6-=(1000000LL*seconds);
    ASSERT( n6 == (1000000LL*seconds) );
    if(0>n6)
        x8=-100*n6;
      else
        x8= 100*n6;
    ASSERT( 0 == (x8 & 0xF8000000) );
    uncertainty_log10 *= (1L<<27); //shift it upwards keeping the sign
    x8 |= (U32)(uncertainty_log10);
    };

void F247_TIME1::SetN3(S64 n3, S32 uncertainty_log10)
    {
    ASSERT( uncertainty_log10 >= -15 && uncertainty_log10 <= 15);
    seconds=n3/1000LL;
    n3-=(1000LL*seconds);
    ASSERT( n3 == (1000LL*seconds) );
    if(0>n3)
        x8=-100000*n3;
      else
        x8= 100000*n3;
    ASSERT( 0 == (x8 & 0xF8000000) );
    uncertainty_log10 *= (1L<<27); //shift it upwards keeping the sign
    x8 |= (U32)(uncertainty_log10);
    };

void F247_TIME1::SetS9(S32 secs, S32 f9, S32 uncertainty_log10)
    {
    ASSERT( uncertainty_log10 >= -15 && uncertainty_log10 <= 15);
    seconds=secs+f9/1000000000L;
    x8=f9%1000000000L;
    x8/=10L;
    ASSERT( 0 == (x8 & 0xF8000000) );
    uncertainty_log10 *= (1L<<27); //shift it upwards keeping the sign
    x8 |= (U32)(uncertainty_log10);
    };

void F247_TIME1::SetS8(S32 secs, S32 f8, S32 uncertainty_log10)
    {
    ASSERT( uncertainty_log10 >= -15 && uncertainty_log10 <= 15);
    seconds=secs+f8/100000000L;
    x8=f8%100000000L;
    ASSERT( 0 == (x8 & 0xF8000000) );
    uncertainty_log10 *= (1L<<27); //shift it upwards keeping the sign
    x8 |= (U32)(uncertainty_log10);
    };

void F247_TIME1::SetS6(S32 secs, S32 f6, S32 uncertainty_log10)
    {
    ASSERT( uncertainty_log10 >= -15 && uncertainty_log10 <= 15);
    seconds=secs+f6/1000000L;
    x8=f6%1000000L;
    x8*=100L;
    ASSERT( 0 == (x8 & 0xF8000000) );
    uncertainty_log10 *= (1L<<27); //shift it upwards keeping the sign
    x8 |= (U32)(uncertainty_log10);
    };

void F247_TIME1::SetS3(S32 secs, S32 f3, S32 uncertainty_log10)
    {
    ASSERT( uncertainty_log10 >= -15 && uncertainty_log10 <= 15);
    seconds=secs+f3/1000L;
    x8=f3%1000L;
    x8*=100000L;
    ASSERT( 0 == (x8 & 0xF8000000) );
    uncertainty_log10 *= (1L<<27); //shift it upwards keeping the sign
    x8 |= (U32)(uncertainty_log10);
    };

S32 F247_TIME1::GetUncertaintyLog10(void)
    {
    return ((S32)(x8 & 0xF8000000)) / (1L<<27);
    };

S32 F247_TIME1::GetSeconds(void)
    {
    return seconds;
    };

S32 F247_TIME1::GetSecondF9(void)
    {
    if(0>seconds)
        return ((S32)(x8 & ~0xF8000000)) * -10;
     else
        return ((S32)(x8 & ~0xF8000000)) *  10;
    };

S32 F247_TIME1::GetSecondF8(void)
    {
    if(0>seconds)
        return -((S32)(x8 & ~0xF8000000));
     else
        return  ((S32)(x8 & ~0xF8000000));
    };

S32 F247_TIME1::GetSecondF6(void)
    {
    if(0>seconds)
        return ((S32)(x8 & ~0xF8000000)) / -100;
     else
        return ((S32)(x8 & ~0xF8000000)) /  100;
    };

S32 F247_TIME1::GetSecondF3(void)
    {
    if(0>seconds)
        return ((S32)(x8 & ~0xF8000000)) / -100000;
     else
        return ((S32)(x8 & ~0xF8000000)) /  100000;
    };

#endif // if __INCLUDE_LEVEL__ == 0

#endif  //_F247_SCALAR_TIME_CPP_

