
#include "map_ava.h"

Map_AVA::Map_AVA(size_t cols, size_t rows) {
	width = cols;
	height = rows;

	//use maloc!
	map = new char*[cols];
	for (int r = 0; r < cols; r++)
		map[r] = new char[rows];
}

//(tennant) I don't think this is needed.
void Map_AVA::map_gen() {
	//(tennant) for top and bottom
	for (int x = 2; x<width - 2; x++)
	{
		map[x][2] = '#';
		map[x][height - 3] = '#';
	}

	//(tennant) for left and right side
	for (int y = 2; y<height - 2; y++)
	{
		map[2][y] = '#';
		map[width - 3][y] = '#';
	}
}

void Map_AVA::set_cell(int w, int h, char c) {
	map[w][h] = c;
}

char Map_AVA::get_cell(int w, int h) {
	char &ret = map[w][h];
	return ret;
}

int Map_AVA::get_width() {
	size_t &w = width;
	return (int)w;
}

int Map_AVA::get_height() {
	size_t &h = height;
	return (int)h;
}