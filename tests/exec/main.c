#include "exec.h"
#include <stdio.h>

int main() {
	struct screen_sizes screens = check_screen_sizes();

	for (int i = 0; i < 4; i++) {
		printf("%d ", screens.sizes[i]);
	}
}
