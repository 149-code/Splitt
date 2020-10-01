#include "main.h"
#include "listener.h"
#include "exec.h"

void do_shortcut(char c, int window) {
	struct screen_sizes screens = get_window_size();
	for (int i = 0; i < 4; i++) {
		printf("%d\n", screens.sizes[i]);
	}
}

int main() {
	start_listener();
}
