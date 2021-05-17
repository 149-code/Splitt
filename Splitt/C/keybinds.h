#ifndef KEYBIND_H
#define KEYBIND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"

struct keybind {
	char escape_char;
	bool is_cursor_swap;
	float window_pos[4];
};

struct keybind_arr {
	struct keybind* arr;
	int len;
};

struct keybind_arr read_keybinds(char* filename);
#endif
