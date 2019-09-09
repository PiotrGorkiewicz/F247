#ifndef __F247_ARGS01_CPP__
#define __F247_ARGS01_CPP__


/* Set in on in M$ systems */
//#define GATES_PATH


#define F247_ARGS01_ARGFILENAME       "args.txt"

#ifndef F247_ARGS01_KEYSIZE
  #define F247_ARGS01_KEYSIZE  50
#endif

#ifndef F247_ARGS01_ARGSIZE
  #define F247_ARGS01_ARGSIZE  200
#endif



#if __INCLUDE_LEVEL__ == 0

#include <stdio.h>
#include <string.h>
#include "f247_parse01.cpp"

#define TEXTBUFSIZE 20

#endif // if __INCLUDE_LEVEL__ == 0



// return size of name found
int F247_ARGS01_get_mainname(char* buffer, char* path, int len_buffer)
#if __INCLUDE_LEVEL__ == 0
    {
    int len_path;
    len_path=strlen(path);
    while(1)
        {
        len_path--;
        #ifdef GATES_PATH
        if((path[len_path]=='\\')||(len_path<0))
        #else
        if((path[len_path]=='/')||(len_path<0))
        #endif
            {
            len_path++;
            strncpy(buffer,path+len_path,len_buffer);
            buffer[len_buffer-1]='\0';
            return strlen(buffer);
            }
        }
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



// 0: does not match
// 1: does match
int F247_ARGS01_compare_mainname
    (
    char* pattern, //must not have any preceding trash
    char* path     //can have a preceding path with '/' (or '\' when GATES_PATH defined)
    )
#if __INCLUDE_LEVEL__ == 0
    {
    int len_path;
    int len_pattern;
    len_path=strlen(path);
    len_pattern=strlen(pattern);
    if(len_path<len_pattern)
        return 0;
    while(1)
        {
        len_path--;
        len_pattern--;
        if(len_pattern<0)
            {
            if(len_path<0)
                return 1;
            #ifdef GATES_PATH
            if(path[len_path]=='\\')
            #else
            if(path[len_path]=='/')
            #endif
                return 1;
            return 0;
            }
        if(pattern[len_pattern]!=path[len_path])
            return 0;
        }
    return 1; //unreachable code
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



//-1:    no match
//other: first character's position following the pattern
#if __INCLUDE_LEVEL__ == 0
static int F247_ARGS01_strcmp(char* pat, char* str)
    {
    int i=0;
    while(pat[i])
        {
        if(pat[i]!=str[i])
            return -1;
        i++;
        }
    return i;
    }
#endif // if __INCLUDE_LEVEL__ == 0



//-1:    key not found
//-2:    invalid value
//other: size of key's value (0 or more)
int F247_ARGS01_find_next
    (
    int argc,
    char** argv,
    int* startarg,
    char* key,
    char* val,
    int valsize
    )
#if __INCLUDE_LEVEL__ == 0
    {
    int i,k;
    FILE* fp_argfile=NULL;
    auto check_and_copy=[&](char* src)->int
        {
        int k=-1;
        int j=F247_ARGS01_strcmp(key,src);
        if(-1!=j)
            {
            for(k=0;;k++)
                {
                if(val!=NULL)
                    {
                    val[k]=src[j+k];
                    if(!val[k])
                        break;
                    if(k==valsize)
                        {
                        k=-2;
                        break;
                        }
                    }
                  else
                    break;
                }
            }
        return k;
        };
    if(argc>1)
        {
        for(i=*startarg;i<argc;i++)
            {
            if(-1==(k=check_and_copy(argv[i])))
                continue;
            *startarg=i;
            return k;
            }
        }
      else
        {
        if(NULL!=(fp_argfile=fopen(F247_ARGS01_ARGFILENAME,"r")))
            {
            char argbuf[F247_ARGS01_ARGSIZE];
            for(i=0;;i++)
                {
                if(0>=F247_PARSE01_fget_anything(fp_argfile, argbuf, F247_ARGS01_ARGSIZE, (char*)"EW", (char*)"EW", NULL))
                    break;
                if(i<*startarg)
                    continue;
                if(-1==(k=check_and_copy(argbuf)))
                    continue;
                *startarg=i;
                return k;
                }
            }
        if(NULL!=fp_argfile)
            fclose(fp_argfile);
        }
    return -1;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



//-1:    key not found
//-2:    invalid value
//other: size of key's value (0 or more)
int F247_ARGS01_find
    (
    int argc,
    char** argv,
    char* key,
    char* val,
    int valsize
    )
#if __INCLUDE_LEVEL__ == 0
    {
    int startarg=0;
    return F247_ARGS01_find_next
        (
        argc,
        argv,
        &startarg,
        key,
        val,
        valsize
        );
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



//-1: key not found
//-2: invalid value
// 0: value ok
int F247_ARGS01_find_U08
    (
    int argc,
    char** argv,
    char* key,
    U08* val
    )
#if __INCLUDE_LEVEL__ == 0
    {
    unsigned int temp;
    int ret;
    char buffer[TEXTBUFSIZE];
    if(0>(ret=F247_ARGS01_find(argc,argv,key,buffer,TEXTBUFSIZE)))
        return ret;
    if(ret==0)
        return -2;
    if(1!=(((buffer[0]=='0')&&((buffer[1]=='x')||(buffer[1]=='X'))) ? sscanf(buffer,"0x%X",&temp) : (sscanf(buffer,"%u",&temp))))
        return -2;
    if(temp>=0x100)
        return -2;
    *val=temp;
    return 0;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



//-1: key not found
//-2: invalid value
// 0: value ok
int F247_ARGS01_find_S08
    (
    int argc,
    char** argv,
    char* key,
    S08* val
    )
#if __INCLUDE_LEVEL__ == 0
    {
    int temp;
    int ret;
    char buffer[TEXTBUFSIZE];
    if(0>(ret=F247_ARGS01_find(argc,argv,key,buffer,TEXTBUFSIZE)))
        return ret;
    if(ret==0)
        return -2;
    if(1!=sscanf(buffer,"%d",&temp))
        return -2;
    if(temp>127 || temp<-128)
        return -2;
    *val=temp;
    return 0;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



//-1: key not found
//-2: invalid value
// 0: value ok
int F247_ARGS01_find_U16
    (
    int argc,
    char** argv,
    char* key,
    U16* val
    )
#if __INCLUDE_LEVEL__ == 0
    {
    unsigned int temp;
    int ret;
    char buffer[TEXTBUFSIZE];
    if(0>(ret=F247_ARGS01_find(argc,argv,key,buffer,TEXTBUFSIZE)))
        return ret;
    if(ret==0)
        return -2;
    if(1!=(((buffer[0]=='0')&&((buffer[1]=='x')||(buffer[1]=='X'))) ? sscanf(buffer,"0x%X",&temp) : (sscanf(buffer,"%u",&temp))))
        return -2;
    *val=temp;
    return 0;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



//-1: key not found
//-2: invalid value
// 0: value ok
int F247_ARGS01_find_S16
    (
    int argc,
    char** argv,
    char* key,
    S16* val
    )
#if __INCLUDE_LEVEL__ == 0
    {
    int temp;
    int ret;
    char buffer[TEXTBUFSIZE];
    if(0>(ret=F247_ARGS01_find(argc,argv,key,buffer,TEXTBUFSIZE)))
        return ret;
    if(ret==0)
        return -2;
    if(1!=sscanf(buffer,"%d",&temp))
        return -2;
    *val=temp;
    return 0;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



//-1: key not found
//-2: invalid value
// 0: value ok
int F247_ARGS01_find_U32
    (
    int argc,
    char** argv,
    char* key,
    U32* val
    )
#if __INCLUDE_LEVEL__ == 0
    {
    unsigned long temp;
    int ret;
    char buffer[TEXTBUFSIZE];
    if(0>(ret=F247_ARGS01_find(argc,argv,key,buffer,TEXTBUFSIZE)))
        return ret;
    if(ret==0)
        return -2;
    if(1!=(((buffer[0]=='0')&&((buffer[1]=='x')||(buffer[1]=='X'))) ? sscanf(buffer,"0x%lX",&temp) : (sscanf(buffer,"%lu",&temp))))
        return -2;
    *val=temp;
    return 0;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



//-1: key not found
//-2: invalid value
// 0: value ok
int F247_ARGS01_find_S32
    (
    int argc,
    char** argv,
    char* key,
    S32* val
    )
#if __INCLUDE_LEVEL__ == 0
    {
    unsigned long temp;
    int ret;
    char buffer[TEXTBUFSIZE];
    if(0>(ret=F247_ARGS01_find(argc,argv,key,buffer,TEXTBUFSIZE)))
        return ret;
    if(ret==0)
        return -2;
    if(1!=(((buffer[0]=='0')&&((buffer[1]=='x')||(buffer[1]=='X'))) ? sscanf(buffer,"0x%lX",&temp) : (sscanf(buffer,"%ld",&temp))))
        return -2;
    *val=temp;
    return 0;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



//-1: key not found
//-2: invalid value
// 0: value ok
int F247_ARGS01_find_double
    (
    int argc,
    char** argv,
    char* key,
    double* val
    )
#if __INCLUDE_LEVEL__ == 0
    {
    double temp;
    int ret;
    char buffer[TEXTBUFSIZE];
    if(0>(ret=F247_ARGS01_find(argc,argv,key,buffer,TEXTBUFSIZE)))
        return ret;
    if(ret==0)
        return -2;
    if(1!=sscanf(buffer,"%lf",&temp))
        return -2;
    *val=temp;
    return 0;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



#endif /* __F247_ARGS01_CPP__ */

