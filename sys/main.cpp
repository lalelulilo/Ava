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

const char* terminal_params = "window: title='Ava', size=80x25"; //(tennent) size is WIDTHxHEIGHT

//TODO (tennent)Move this outside main.
/*
=================
map

	(tennent) Generates a single array with "walls". The array will (could be) used for collision and other 
	environmental stuff. This was a tricky due to BearLib reversing the traditional ROW vs COL 
	to COL vs ROW for its terminals grid.
=================
*/
template <size_t cols, size_t rows>
void map_gen(char (&map)[cols][rows]) {

	//(tennant) for top and bottom
	for (int x = 2; x<cols - 2; x++)
	{
		map[x][2] = '#';
		map[x][rows - 3] = '#';
	}

	//(tennant) for left and right side
	for (int y = 2; y<rows - 2; y++)
	{
		map[2][y] = '#';
		map[cols - 3][y] = '#';
	}
}

//TODO (tennent)Move this outside main.
/*
=================
map

	(tennent) For now this will border the window with "walls".
=================
*/
void map() {
	//(tennant) predetermined window sizes for now. Can figure out dynamic changes later. Arrays probably aren't the best soln here.
	const int width = 80;
	const int height = 25;

	char simple_map[height][width];
	//(tennent) Pad map with ' '. Probably not best practice! Also side effects.
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			simple_map[i][j] = ' ';
		}
	}

	//(tennent) Setting "envioronment" layer to 1 for the time being.
	terminal_layer(1);

	//generate a simple map
	map_gen(simple_map);

	//(tennent) Iterate through array and place the characters on screen.
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (simple_map[i][j] == '#')
				terminal_put(j, i, simple_map[i][j]);
		}
	}
}

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