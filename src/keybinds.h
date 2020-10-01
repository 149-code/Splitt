#ifndef KEYBIND_H
#define KEYBIND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct keybind {
	char escape_char;
	float window_pos[4];
};

struct keybind_arr {
	struct keybind* arr;
	int len;
};

struct keybind_arr read_keybinds(char* filename);
#endif
