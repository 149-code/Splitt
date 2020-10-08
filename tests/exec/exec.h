#ifndef EXEC_H
#define EXEC_H

#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <Carbon/Carbon.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct screen_size {
	float x;
	float y;
	float dx;
	float dy;
};

struct screen_sizes {
	struct screen_size* arr;
	int len;
};

int get_frontmost_application();
struct screen_sizes get_desktop_sizes();
struct screen_size get_window_size();
void resize_current_window(int p1, int p2, int p, int p4);

#endif
