#include "main.h"

int get_current_window(struct screen_sizes desktop_sizes, struct screen_size window)
{
	for (int i = 0; i < desktop_sizes.len; i++) {
		struct screen_size curr = desktop_sizes.arr[i];
		if (curr.x <= window.x && curr.y <= window.y && 
				curr.x + curr.dx >= window.x + window.dx && 
				curr.x + curr.dx >= window.x + window.dx) {
			return i;
		}
	}

	return -1;
}

void do_shortcut(char c, int window)
{
	struct screen_sizes desktop_sizes = get_desktop_sizes();
	struct screen_size window_size = get_window_size();
	struct keybind_arr keybinds = read_keybinds("data/keybinds");

	struct screen_size curr_desktop = desktop_sizes.arr[get_current_window(
			desktop_sizes, window_size)];

	for (int i = 0; i < keybinds.len; i++) {
		if (keybinds.arr[i].escape_char == c) {

			if (window == -1) {
				resize_current_window(
						curr_desktop.x + curr_desktop.dx * (keybinds.arr[i].window_pos[0]),
						curr_desktop.y + curr_desktop.dy * (keybinds.arr[i].window_pos[1]),
						curr_desktop.x + curr_desktop.dx * (keybinds.arr[i].window_pos[2]),
						curr_desktop.y + curr_desktop.dy * (keybinds.arr[i].window_pos[3]));
			}
		}
	}
}

int main()
{
	start_listener();
}
