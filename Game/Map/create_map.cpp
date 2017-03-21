/*
=================
create_map.cpp

TODO (tennent) Proper class documentation will be requierd. As we flesh out the perpose of each class we can
update the documentation.

This class, all assosiated classes, will be responsible for map generation.
	-(tennant) Currently a simple border is being generated inside of a fixed window. The next step will probably be to
	 turn the map into an object that can be used for collion detection and new area generation.
=================
*/

#include "BearLibTerminal.h"
#include "map.h"

/*
=================
map_gen

(tennent) Generates a single array with "walls". The array will (could be) used for collision and other
environmental stuff. This was a tricky due to BearLib reversing the traditional ROW vs COL
to COL vs ROW for its terminals grid.
=================
*/
void map_gen( Map_AVA map ) {

	size_t cols = map.get_width();
	size_t rows = map.get_height();

	//(tennant) for top and bottom
	for (int x = 2; x<cols - 2; x++)
	{
		map.set_cell(x, 2, '#');
		map.set_cell(x, ((int)rows - 3), '#');
	}

	//(tennant) for left and right side
	for (int y = 2; y<rows - 2; y++)
	{
		map.set_cell(2, y, '#');
		map.set_cell(((int)cols - 3), y, '#');
	}
}

/*
=================
create_map

(tennent) For now this will border the window with "walls".
=================
*/
void create_map() {
	//(tennant) predetermined window sizes for now. Can figure out dynamic changes later. Arrays probably aren't the best soln here.
	const int width = 80;
	const int height = 25;

	Map_AVA simple_map(width, height);

	//(tennent) Setting "envioronment" layer to 1 for the time being.
	terminal_layer(1);

	//generate a simple map
	map_gen(simple_map);

	//(tennent) Iterate through array and place the characters on screen.
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if ((int)simple_map.get_cell(i ,j) == '#')
				terminal_put(i, j, simple_map.get_cell(i, j));
		}
	}
}