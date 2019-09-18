#ifndef _F247_DB_SQLITE_CPP_
#define _F247_DB_SQLITE_CPP_



#include "f247_pee.cpp"

#include "f247_allocatable.cpp"

#include <sqlite3.h>



#define F247_PREV             F247_ALLOCATABLE
#define F247_THIS             F247_DB_SQLITE



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_="");
    virtual ~F247_THIS();
  public:
    virtual void SetParams(int _argc, char** _argv);
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  public:
    virtual F247_ACT_STATUS Allocate(void* arg);
    virtual F247_ACT_STATUS Free(void* arg);
  protected:
    int argc;
    char** argv;
  protected:
    static int Cb
        (
        void* context,
        int argc,
        char** argv,
        char** err
        );
    sqlite3* db;
    };



#if __INCLUDE_LEVEL__ == 0



#include <stdio.h>



int F247_THIS::Cb
    (
    void* context,
    int cols,
    char** colVals,
    char** colNames
    )
    {
//    F247_THIS* thiss=(F247_THIS*)context;
    printf("Cb: ");
    for(int i=0; i<cols; i++)
        printf("[%s]=(%s) ",colNames[i],colVals[i]!=NULL?colVals[i]:"NULL");
    printf("\n");
    return 0;
    }



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_)
    {
    to_allocate=1;
    db=NULL;
    argc=0;
    argv=NULL;
    Log_Cons();
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    }



#if 0
13  int main(int argc, char **argv){
14    sqlite3 *db;
15    char *zErrMsg = 0;
16    int rc;
17  
18    if( argc!=3 ){
19      fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
20      return(1);
21    }
22    rc = sqlite3_open(argv[1], &db);
23    if( rc ){
24      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
25      sqlite3_close(db);
26      return(1);
27    }
28    rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
29    if( rc!=SQLITE_OK ){
30      fprintf(stderr, "SQL error: %s\n", zErrMsg);
31      sqlite3_free(zErrMsg);
32    }
33    sqlite3_close(db);
34    return 0;
35  }
#endif



F247_ACT_STATUS F247_THIS::Allocate(void* arg)
    {
    int err;
    printf("Sqlite (#01): \n" );fflush(stdout);
    switch(to_allocate)
        {
        case 1:
            {
            F247_Pee("a_debug");
            err=sqlite3_open("F247-demo.sqlite",&db);
            if(err)
                {
                printf("Sqlite error (#00): %s\n", sqlite3_errmsg(db) );fflush(stdout);
                Free(arg);
                printf("Sqlite (#07): \n" );fflush(stdout);
                return F247_ACT_STATUS_ErrResource;
                }
            to_allocate--;
            printf("Sqlite (#02): \n" );fflush(stdout);
            return F247_ACT_STATUS_Done;
            // no break!
            }
        case 0:
            return F247_ACT_STATUS_Skipped;
        default:
            return F247_ACT_STATUS_ErrFatal;
        } //switch(to_allocate)
    }



F247_ACT_STATUS F247_THIS::Free(void* arg)
    {
    printf("Sqlite (#04): \n" );fflush(stdout);
    switch(to_allocate)
        {
        case 0:
            {
	    sqlite3_close(db);
            to_allocate++;
            printf("Sqlite (#05): \n" );fflush(stdout);
            return F247_ACT_STATUS_Done;
            // no break!
            }
        case 1:
            return F247_ACT_STATUS_Skipped;
        default:
            return F247_ACT_STATUS_ErrFatal;
        } //switch(to_allocate)
    }



void F247_THIS::SetParams(int _argc, char** _argv)
    {
    argc=_argc;
    argv=_argv;
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_DB_SQLITE_CPP_

