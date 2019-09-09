#ifndef _F247_AUD_PORTAUDIO_CPP_
#define _F247_AUD_PORTAUDIO_CPP_



#include "portaudio.h"

#include "f247_aud.cpp"

#include "f247_args01.cpp"



#define F247_PREV             F247_AUD
#define F247_THIS             F247_AUD_PORTAUDIO



typedef F247_AUD_VAL PORTAUDIO_SINGLE;



class F247_THIS : public F247_PREV
    {
  public:
    F247_THIS(const char* id_str_="");
    virtual ~F247_THIS();
  public:
    virtual const char* TypeName(void)         {return xstr(F247_THIS);}  //must be copied
  public:
    virtual F247_ACT_STATUS Allocate(void* arg);
    virtual F247_ACT_STATUS Free(void* arg);
    virtual F247_ACT_STATUS UpdateOutputs(void* arg);
    virtual F247_ACT_STATUS UpdateTime(void* arg);
  protected:
    static int OutCb
        (
        const void* inputBuffer,
        void* outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData
        );
  protected:
    PaStream* stream;
  public:
    F247_SIG_INPUT inpL;
    F247_SIG_INPUT inpR;
    };



#if __INCLUDE_LEVEL__ == 0



#include <stdio.h>



int F247_THIS::OutCb
    (
    const void* inputBuffer,
    void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData
    )
    {
    F247_THIS* thiss=(F247_THIS*)userData; 
    PORTAUDIO_SINGLE* sptr= (PORTAUDIO_SINGLE*)outputBuffer;
    unsigned long i;
    (void) inputBuffer; // Prevent unused variable warning
    for(i=0; i<framesPerBuffer; i++)
        {
        *sptr++=thiss->inpL.val;
        *sptr++=thiss->inpR.val;
        thiss->OutUpdateTime();
        }
    return 0;
    }



F247_ACT_STATUS F247_THIS::UpdateOutputs(void* arg)
    {
    return F247_ACT_STATUS_Done;
    }



F247_ACT_STATUS F247_THIS::UpdateTime(void* arg)
    {
    return F247_ACT_STATUS_Done;
    }



F247_THIS::F247_THIS(const char* id_str_) : F247_PREV(id_str_)
    {
    to_allocate=3;
    inpL.AppendMe(&inputs);
    inpR.AppendMe(&inputs);
    inpL.val=0.0;
    inpR.val=0.0;
    Log_Cons();
    }



F247_THIS::~F247_THIS()
    {
    Log_Dest();
    }



F247_ACT_STATUS F247_THIS::Allocate(void* arg)
    {
    PaError err;
    switch(to_allocate)
        {
        case 3:
            {
            err=Pa_Initialize();
            if(err!=paNoError)
                {
                printf("PortAudio error (#00): %s\n", Pa_GetErrorText( err ) );
                Free(arg);
                return F247_ACT_STATUS_ErrResource;
                }
            to_allocate--;
            // no break!
            }
        case 2:
            {
            err=Pa_OpenDefaultStream
                ( 
                &(this->stream),
                0,//input channels
                2,//output channels
                paInt16,//signed 16-bit
                44100,//sampling
                256,// or paFramesPerBufferUnspecified
                F247_THIS::OutCb,//callback
                this //context
                );
            if(err!=paNoError)
                {
                printf("PortAudio error (#01): %s\n", Pa_GetErrorText( err ) );
                Free(arg);
                return F247_ACT_STATUS_ErrResource;
                }
            to_allocate--;
            // no break!
            }
        case 1:
            {
            err=Pa_StartStream( this->stream );
            if(err!=paNoError)
                {
                printf("PortAudio error (#02): %s\n", Pa_GetErrorText( err ) );
                Free(arg);
                return F247_ACT_STATUS_ErrResource;
                }
            to_allocate--;
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
    PaError err;
    switch(to_allocate)
        {
        case 0:
            {
            err=Pa_StopStream( this->stream );
            if(err!=paNoError)
                {
                printf("PortAudio error (#12): %s\n", Pa_GetErrorText( err ) );
                return F247_ACT_STATUS_ErrResource;
                }
            to_allocate++;
            // no break!
            }
        case 1:
            {
            err=Pa_CloseStream( this->stream );
            if(err!=paNoError)
                {
                printf("PortAudio error (#11): %s\n", Pa_GetErrorText( err ) );
                return F247_ACT_STATUS_ErrResource;
                }
            to_allocate++;
            // no break!
            }
        case 2:
            {
            err=Pa_Terminate();
            if(err!=paNoError)
                {
                printf("PortAudio error (#10): %s\n", Pa_GetErrorText( err ) );
                return F247_ACT_STATUS_ErrResource;
                }
            to_allocate++;
            return F247_ACT_STATUS_Done;
            // no break!
            }
        case 3:
            return F247_ACT_STATUS_Skipped;
        default:
            return F247_ACT_STATUS_ErrFatal;
        } //switch(to_allocate)
    }



#endif // if __INCLUDE_LEVEL__ == 0



#undef F247_PREV
#undef F247_THIS



#endif //_F247_AUD_PORTAUDIO_CPP_

