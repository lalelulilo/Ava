#pragma once

class Map_AVA {
	size_t width, height;
	char** map;

public:
	Map_AVA(size_t, size_t);

	void map_gen();
	void set_cell(int, int, char);
	char get_cell(int, int);
	int get_width();
	int get_height();
};