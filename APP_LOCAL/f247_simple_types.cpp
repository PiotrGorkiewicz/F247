#ifndef   _F247_SIMPLE_TYPES_CPP_
#define   _F247_SIMPLE_TYPES_CPP_

typedef unsigned char      U08;
typedef   signed char      S08;
typedef unsigned short     U16;
typedef   signed short     S16;
typedef unsigned long      U32;
typedef   signed long      S32;
typedef unsigned long long U64;
typedef   signed long long S64;

typedef unsigned int UATOM;
typedef unsigned int BULL;
typedef   signed int SATOM;

#ifndef HW_BITSINWORD   /* must be just: 8, 16, 32, or 64 */
    //#warning : HW_BITSINWORD undefined, 32 assumed. Possibility of inefficient code to be generated!
    #define HW_BITSINWORD 32
#endif

#if (HW_BITSINWORD >  64)
    #error !!! Invalid HW_BITSINWORD: should be 8, 16, 32, or 64
#elif (HW_BITSINWORD == 64)
    typedef U64 U64p;
    typedef U64 U48p;
    typedef U64 U32p;
    typedef U64 U24p;
    typedef U64 U16p;
    typedef U64 U12p;
    typedef U64 U10p;
    typedef U64 U08p;
    typedef S64 S64p;
    typedef S64 S48p;
    typedef S64 S32p;
    typedef S64 S24p;
    typedef S64 S16p;
    typedef S64 S12p;
    typedef S64 S10p;
    typedef S64 S08p;
#elif (HW_BITSINWORD >= 32)
    typedef U64 U64p;
    typedef U64 U48p;
    typedef U32 U32p;
    typedef U32 U24p;
    typedef U32 U16p;
    typedef U32 U12p;
    typedef U32 U10p;
    typedef U32 U08p;
    typedef S64 S64p;
    typedef S64 S48p;
    typedef S32 S32p;
    typedef S32 S24p;
    typedef S32 S16p;
    typedef S32 S12p;
    typedef S32 S10p;
    typedef S32 S08p;
#elif (HW_BITSINWORD >= 16)
    typedef U64 U64p;
    typedef U64 U48p;
    typedef U32 U32p;
    typedef U32 U24p;
    typedef U16 U16p;
    typedef U16 U12p;
    typedef U16 U10p;
    typedef U16 U08p;
    typedef S64 S64p;
    typedef S64 S48p;
    typedef S32 S32p;
    typedef S32 S24p;
    typedef S16 S16p;
    typedef S16 S12p;
    typedef S16 S10p;
    typedef S16 S08p;
#elif (HW_BITSINWORD >=  8)
    typedef U64 U64p;
    typedef U64 U48p;
    typedef U32 U32p;
    typedef U32 U24p;
    typedef U16 U16p;
    typedef U16 U12p;
    typedef U16 U10p;
    typedef U08 U08p;
    typedef S64 S64p;
    typedef S64 S48p;
    typedef S32 S32p;
    typedef S32 S24p;
    typedef S16 S16p;
    typedef S16 S12p;
    typedef S16 S10p;
    typedef S08 S08p;
#else
    #error *** Invalid HW_BITSINWORD: should be 8, 16, 32, or 64
#endif

#define JOIN(a, ...) JOIN_PRIMITIVE(a, __VA_ARGS__)
#define JOIN_PRIMITIVE(a, ...) a ## __VA_ARGS__


#endif  //_F247_SIMPLE_TYPES_CPP_


