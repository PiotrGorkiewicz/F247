#ifndef   _F247_LOG_COUNT_CPP_
#define   _F247_LOG_COUNT_CPP_

#if __INCLUDE_LEVEL__ == 0

#include <stdio.h>
#include <time.h>

#define F247_LOG_COUNT_POINTS 10

long F247_log_count_points[F247_LOG_COUNT_POINTS];

void F247_LogCount(int p)
    {
    static time_t T=time(NULL);
    time_t T1=time(NULL);
    if(p<F247_LOG_COUNT_POINTS)
        F247_log_count_points[p]++;
    if(T1!=T)
        {
        T=T1;
        for(int i=0; i!=F247_LOG_COUNT_POINTS; i++)
            {
            if (0!=F247_log_count_points[i])
                printf("F247_log_count_points[%d]=%ld\n",i,F247_log_count_points[i]);
            }
        }
    }

#else // if __INCLUDE_LEVEL__ == 0

extern void F247_LogCount(int p);

#endif // if __INCLUDE_LEVEL__ == 0



#endif  //_F247_LOG_COUNT_CPP_

