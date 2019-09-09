#ifndef   _F247_SDL2_EVENT_CPP_
#define   _F247_SDL2_EVENT_CPP_



#include "f247_event.cpp"

#include <SDL.h>



#define F247_PREV  F247_EVENT
#define F247_THIS  F247_SDL2_EVENT



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_="") : F247_PREV(id_str_) {Log_Cons();};
    virtual ~F247_THIS() {Log_Dest();}
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  public:
    void CopyFromSdlEv(SDL_Event* p);
  protected:
    SDL_Event sdlev;
    };



#if __INCLUDE_LEVEL__ == 0



#include <SDL2/SDL_ttf.h>
#include <assert.h>
//#define NDEBUG //uncomment it to turn off assert



void F247_THIS::CopyFromSdlEv(SDL_Event* p) {sdlev=*p;}



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif  //_F247_SDL2_EVENT_CPP_

