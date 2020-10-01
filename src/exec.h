#ifndef EXEC_H
#define EXEC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct screen_sizes {
	int num_screens;
	int* sizes;
};

struct screen_sizes get_desktop_size();
struct screen_sizes get_window_size();
void resize_current_window(int p1, int p2, int p, int p4);

#endif
