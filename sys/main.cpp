/*
=================
main.cpp

TODO (tennent) Proper class documentation will be requierd. As we flesh out the perpose of each class we can 
			   update the documentation.

The main entry point for AVA. This class will include the main game loop (among other things).
=================
*/

/* (tszucs): This allows us to start from main() instead of WinMain().. */
#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "BearLibTerminal.h"
#include "../havenlib/precompiled.h"
#include "../Game/Map/map.h"

const char* terminal_params = "window: title='Ava', size=80x25"; //(tennent) size is WIDTHxHEIGHT

int main() {

	//(tennant) add debug info
	terminal_open();

	//(tennant) add debug info
	//(tennent) set terminal parameters.
	terminal_set(terminal_params);

	//(tennant) add debug info
	terminal_clear();

	//(tennant) draw the map in the terminal.
	map();

	//(tennant) add debug info
	terminal_refresh();

	//(tennent) wait for close.
	while (terminal_read() != TK_CLOSE);

	//(tennant) add debug info
	terminal_close();

	DebugPrintf(VERBOSITY_SYS, "Waiting for terminal to be closed..\n");

	return 0;
}