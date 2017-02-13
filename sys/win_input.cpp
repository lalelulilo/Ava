/* Windows related input */

#include <assert.h>

#include "win_local.h"

/* TODO(szucs): We probably want to map these to some defined keys for the
       game, and then return that key value.. but for now we'll just return
       S_OK to indicate no errors

   Virtual-Key table at:
   https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
*/
int Input_KeyboardEvent( RAWINPUT *inputData ) {
    bool isDown;
    bool wasDown;

    assert(inputData != NULL);
    assert(inputData->header.dwType == RIM_TYPEKEYBOARD);

    isDown = ( (inputData->data.keyboard.Message & (1 << 31)) != 0 );
    wasDown = ( (inputData->data.keyboard.Message & (1 << 30)) != 0 );

    // TODO(szucs): Handle input
    switch( inputData->data.keyboard.VKey ) {
    case 'W':
    case 'A':
    case 'S':
    case 'D':
    case VK_SPACE:
    case VK_ESCAPE:
    default:
        break;
    }

    return S_OK;
}

/* TODO(szucs): Maybe we want to create a mouse structure with info for
   the game like x & y position, and a button action

   RAWINPUT for mouse at:
   https://msdn.microsoft.com/en-us/library/windows/desktop/ms645578(v=vs.85).aspx
*/
int Input_MouseEvent( RAWINPUT *inputData ) {
    assert( inputData != NULL );
    assert( inputData->header.dwType == RIM_TYPEMOUSE );

    // Process mouse movement
    switch ( inputData->data.mouse.usFlags ) {
    case MOUSE_ATTRIBUTES_CHANGED:
    case MOUSE_MOVE_RELATIVE:
    case MOUSE_MOVE_ABSOLUTE:
    case MOUSE_VIRTUAL_DESKTOP: // NOTE(szucs): not sure if we need this
    default:
        break;
    }

    // Process mouse buttons
    switch( inputData->data.mouse.usButtonFlags ) {
    case RI_MOUSE_LEFT_BUTTON_DOWN:
    case RI_MOUSE_LEFT_BUTTON_UP:
    case RI_MOUSE_RIGHT_BUTTON_DOWN:
    case RI_MOUSE_RIGHT_BUTTON_UP:
    default:
        break;
    }

    return S_OK;
}

int Input_Init( void ) {
    // Register keyboard
    win32.keyboard.usUsagePage = 0x01;
    win32.keyboard.usUsage = 0x02;
    win32.keyboard.dwFlags = RIDEV_NOLEGACY;    // Ignore legacy mouse messages
    win32.keyboard.hwndTarget = 0;

    if ( !RegisterRawInputDevices( &win32.keyboard, 1, sizeof(RAWINPUTDEVICE) ) ) {
        // TODO(szucs): Log GetLastError
        return GetLastError();
    }

    // Register mouse
    win32.mouse.usUsagePage = 0x01;
    win32.mouse.usUsage = 0x06;
    win32.mouse.dwFlags = RIDEV_NOLEGACY;    // Ignore legacy mouse messages
    win32.mouse.hwndTarget = 0;

    if ( !RegisterRawInputDevices( &win32.mouse, 1, sizeof(RAWINPUTDEVICE) ) ) {
        // TODO(szucs): Log GetLastError
        return GetLastError();
    }

    return S_OK;
}
