#ifndef   _F247_PEE_CPP_
#define   _F247_PEE_CPP_

#ifndef STRIPPATH
  #define STRIPPATH(s)\
   (sizeof(s) >  2 && (s)[sizeof(s)- 2] == '/' ? (s) + sizeof(s) -  1 : \
    sizeof(s) >  3 && (s)[sizeof(s)- 3] == '/' ? (s) + sizeof(s) -  2 : \
    sizeof(s) >  4 && (s)[sizeof(s)- 4] == '/' ? (s) + sizeof(s) -  3 : \
    sizeof(s) >  5 && (s)[sizeof(s)- 5] == '/' ? (s) + sizeof(s) -  4 : \
    sizeof(s) >  6 && (s)[sizeof(s)- 6] == '/' ? (s) + sizeof(s) -  5 : \
    sizeof(s) >  7 && (s)[sizeof(s)- 7] == '/' ? (s) + sizeof(s) -  6 : \
    sizeof(s) >  8 && (s)[sizeof(s)- 8] == '/' ? (s) + sizeof(s) -  7 : \
    sizeof(s) >  9 && (s)[sizeof(s)- 9] == '/' ? (s) + sizeof(s) -  8 : \
    sizeof(s) > 10 && (s)[sizeof(s)-10] == '/' ? (s) + sizeof(s) -  9 : \
    sizeof(s) > 11 && (s)[sizeof(s)-11] == '/' ? (s) + sizeof(s) - 10 : \
    sizeof(s) > 12 && (s)[sizeof(s)-12] == '/' ? (s) + sizeof(s) - 11 : \
    sizeof(s) > 13 && (s)[sizeof(s)-13] == '/' ? (s) + sizeof(s) - 12 : \
    sizeof(s) > 14 && (s)[sizeof(s)-14] == '/' ? (s) + sizeof(s) - 13 : \
    sizeof(s) > 15 && (s)[sizeof(s)-15] == '/' ? (s) + sizeof(s) - 14 : \
    sizeof(s) > 16 && (s)[sizeof(s)-16] == '/' ? (s) + sizeof(s) - 15 : \
    sizeof(s) > 17 && (s)[sizeof(s)-17] == '/' ? (s) + sizeof(s) - 16 : \
    sizeof(s) > 18 && (s)[sizeof(s)-18] == '/' ? (s) + sizeof(s) - 17 : \
    sizeof(s) > 19 && (s)[sizeof(s)-19] == '/' ? (s) + sizeof(s) - 18 : \
    sizeof(s) > 20 && (s)[sizeof(s)-20] == '/' ? (s) + sizeof(s) - 19 : \
    sizeof(s) > 21 && (s)[sizeof(s)-21] == '/' ? (s) + sizeof(s) - 20 : \
    sizeof(s) > 22 && (s)[sizeof(s)-22] == '/' ? (s) + sizeof(s) - 21 : \
    sizeof(s) > 23 && (s)[sizeof(s)-23] == '/' ? (s) + sizeof(s) - 22 : \
    sizeof(s) > 24 && (s)[sizeof(s)-24] == '/' ? (s) + sizeof(s) - 23 : \
    sizeof(s) > 25 && (s)[sizeof(s)-25] == '/' ? (s) + sizeof(s) - 24 : \
    sizeof(s) > 26 && (s)[sizeof(s)-26] == '/' ? (s) + sizeof(s) - 25 : \
    sizeof(s) > 27 && (s)[sizeof(s)-27] == '/' ? (s) + sizeof(s) - 26 : \
    sizeof(s) > 28 && (s)[sizeof(s)-28] == '/' ? (s) + sizeof(s) - 27 : \
    sizeof(s) > 29 && (s)[sizeof(s)-29] == '/' ? (s) + sizeof(s) - 28 : \
    sizeof(s) > 30 && (s)[sizeof(s)-30] == '/' ? (s) + sizeof(s) - 29 : \
    sizeof(s) > 31 && (s)[sizeof(s)-31] == '/' ? (s) + sizeof(s) - 30 : \
    (s))
#endif //STRIPPATH

#ifndef __JUST_FILE__
  #define __JUST_FILE__ STRIPPATH(__FILE__)
#endif

#ifndef F247_Pee
  #define F247_Pee(x) printf("F247: FILE:%s LINE:%d FUNC:%s (%s)\n",__JUST_FILE__,__LINE__,__PRETTY_FUNCTION__,(x));
#endif

#endif  //_F247_PEE_CPP_

