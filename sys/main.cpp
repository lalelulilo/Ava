/* Entry point for AVA */

/* Note(tszucs): This allows us to start from main() instead of WinMain().. */
#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <vector>

#include "BearLibTerminal.h"
#include "../havenlib/precompiled.h"

const char* terminal_params = "window: title='Ava', size=80x25"; //(tennent) size is WIDTHxHEIGHT
const int width = TK_WIDTH;

//TODO (tennent)Move this outside main.
/*
=================
map

(tennent) Generates a single array with "walls". The array will (could be) used for collision and other environmental stuff.
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
int map() {

	//(tennant) probably shouldn't be done here.
	terminal_set(terminal_params); 

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
	

	terminal_clear();

	//(tennent) Setting "envioronment" layer to 1 for the time being.
	terminal_layer(1);

	//generate a simple map
	map_gen(simple_map);

	//(tennent) Iterate through array and place the characters.
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (simple_map[i][j] == '#')
				terminal_put(j, i, simple_map[i][j]);
		}
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