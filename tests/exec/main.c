#include "exec.h"
#include <stdio.h>

int main() {
	resize_current_window(50, 50, 595, 360);

	struct screen_size screen = get_window_size();
	printf("%f %f %f %f\n", screen.x, screen.y, screen.dx, screen.dy);
}
