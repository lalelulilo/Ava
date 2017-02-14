/* Entry point for Windows */

#include <stdint.h>
#include <stdio.h>

#include "win_local.h"
#include "../../havenlib/precompiled.h"

/* Global variable */
Win32Vars_t win32 = { 0 };

static LRESULT CALLBACK MainWindowCallback( HWND window, UINT message, WPARAM wParam, LPARAM lParam ) {
    LRESULT result = 0;

    switch (message) {
    case WM_ACTIVATEAPP:
    {
        OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;

    case WM_INPUT:
    {
        /* TODO(szucs): I think this is the wrong spot for this */
        RAWINPUT inputData;
        UINT dataSize;

        GetRawInputData( (HRAWINPUT)lParam,
                         RID_INPUT,
                         &inputData,
                         &dataSize,
                         sizeof(RAWINPUTHEADER) );

        if ( inputData.header.dwType == RIM_TYPEKEYBOARD ) {
            // TODO(szucs): do something with the keyboard event
            Input_KeyboardEvent( &inputData );
        } else if ( inputData.header.dwType == RIM_TYPEMOUSE ) {
            // TODO(szucs): do something with the mouse event
            Input_MouseEvent( &inputData );
        }
    } break;

    default:
    {
        result = DefWindowProcA(window, message, wParam, lParam);
    } break;
    }

    return result;
}

int CALLBACK WinMain( HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowCode ) {
    WNDCLASSA windowClass = {};
    HWND window;

    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = MainWindowCallback;
    windowClass.hInstance = Instance;
    windowClass.lpszClassName = "AVAWindowClass";

    if ( FAILED( RegisterClassA(&windowClass) ) ) {
        // TODO(szucs): We've failed, better log it
        return -1;
    }

    window = CreateWindowExA( 0,
                              windowClass.lpszClassName,
                              "AVA",
                              WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                              CW_USEDEFAULT,
                              CW_USEDEFAULT,
                              CW_USEDEFAULT,
                              CW_USEDEFAULT,
                              0, 0, Instance, 0 );

    if (!window) {
        // TODO(szucs): We've failed, better log it
        return -1;
    }

    if ( FAILED( Input_Init() ) ) {
        // TODO(szucs): Log error code
    }

    /* TODO(szucs): Likely not the ideal place for this, but keep
       it here for now to prove it works
    */
    havenLib::Init();

    DebugPrintf( VERBOSITY_SYS, "If I was a game loop I'd probably go here\n" );

    havenLib::Deinit();
    return 0;
}

