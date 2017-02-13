#ifndef __WIN_LOCAL_H__
#define __WIN_LOCAL_H__

#include <windows.h>
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <stdint.h>

/* RawInput */
int Input_KeyboardEvent( RAWINPUT *inputData );
int Input_MouseEvent( RAWINPUT *inputData );
int Input_Init( void );

/* WASAPI */
int Sound_FillSoundBuffer( BYTE *sourceBuffer, uint32_t samplesToWrite );
int Sound_Init( int samplesPerSecond );

typedef struct {
    HWND          hWnd;         // Main window
    HINSTANCE     hInstance;    // Application instance 
    WNDPROC       hWndProc;     // Callback to process window msg 

    /* RawInput */
    RAWINPUTDEVICE     mouse;
    RAWINPUTDEVICE     keyboard;

    /* XAudio2 */
    IXAudio2               *soundEngine;
    IXAudio2MasteringVoice *masterVoice;
    IXAudio2SourceVoice    *sourceVoice;
} Win32Vars_t;

extern Win32Vars_t win32;

#endif /* !__WIN_LOCAL_H__ */
