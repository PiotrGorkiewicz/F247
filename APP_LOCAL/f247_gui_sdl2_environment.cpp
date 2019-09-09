#ifndef _F247_GUI_SDL2_ENVIRONMENT_CPP_
#define _F247_GUI_SDL2_ENVIRONMENT_CPP_



#include "f247_allocatable.cpp"

#include <SDL.h>



#define F247_PREV             F247_ALLOCATABLE
#define F247_THIS             F247_GUI_SDL2_ENVIRONMENT



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_="");
    virtual ~F247_THIS();
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  protected:
    int sdl_handle;
  public:
    virtual F247_ACT_STATUS Allocate(void* arg);
    virtual F247_ACT_STATUS Free(void* arg);
    virtual F247_ACT_STATUS IsAllocated(void* arg);
    };



#if __INCLUDE_LEVEL__ == 0



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_)
    {
    Log_Cons();
    sdl_handle=-1;
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    }



F247_ACT_STATUS F247_THIS::Allocate(void* arg)
    {
    if(0>sdl_handle)
        {
        sdl_handle=SDL_Init(SDL_INIT_EVERYTHING);
        if(0>sdl_handle)
            return F247_ACT_STATUS_ErrResource;
        return F247_ACT_STATUS_Done;
        }
    return F247_ACT_STATUS_Skipped;
    }



F247_ACT_STATUS F247_THIS::Free(void* arg)
    {
    if(0>sdl_handle)
        return F247_ACT_STATUS_Skipped;
    sdl_handle=-1;
    SDL_Quit();
    return F247_ACT_STATUS_Done;
    }



F247_ACT_STATUS F247_THIS::IsAllocated(void* arg)
    {
    if(0>sdl_handle)
        return F247_ACT_STATUS_False;
      else
        return F247_ACT_STATUS_True;
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_GUI_SDL2_ENVIRONMENT_CPP_

