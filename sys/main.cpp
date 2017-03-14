/* Entry point for AVA */

/* Note(tszucs): This allows us to start from main() instead of WinMain().. */
#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "BearLibTerminal.h"
#include "../havenlib/precompiled.h"

const char* terminal_params = "window: title='Ava', size=80x25";

//TODO (tennent)Move this outside main.
/*
=================
map

	(tennent) For now this will border the window with "walls".
=================
*/
int map() {
	int width;
	int height;

	//(tennant) probably shouldn't be done here.
	terminal_set(terminal_params); 

	terminal_clear();

	//(tennent) Setting "envioronment" layer to 1 for the tiem being.
	terminal_layer(1);

	width = terminal_state(TK_WIDTH);
	height = terminal_state(TK_HEIGHT);

	//(tennant) bordering current window as the first "room". Can these loops be combined?
	//(tennent) for top and bottom
	for (int x = 2; x<width-2; x++)
	{
		terminal_put(x, 2, (int)'#');
		terminal_put(x, height - 3, (int)'#');
	}

	//(tennant) for left and right side
	for (int y = 2; y<height-2; y++)
	{
		terminal_put(2, y, (int)'#');
		terminal_put(width - 3, y, (int)'#');
	}

	terminal_refresh();

	while (terminal_read() != TK_CLOSE);

	return 0;
}

int main() {
	terminal_open();

	while (map());

	terminal_close();

	DebugPrintf(VERBOSITY_SYS, "Waiting for terminal to be closed..\n");
}