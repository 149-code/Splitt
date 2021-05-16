#include "logic.h"

int get_current_window(struct screen_sizes desktop_sizes, struct screen_size window)
{
	for (int i = 0; i < desktop_sizes.len; i++)
	{
		struct screen_size curr = desktop_sizes.arr[i];
		if (curr.x <= window.x && curr.y <= window.y &&
			curr.x + curr.dx >= window.x + window.dx &&
			curr.x + curr.dx >= window.x + window.dx)
		{
			return i;
		}
	}

	return -1;
}

void do_resize(struct screen_size curr_desktop, struct keybind curr_keybind)
{
	resize_current_window(curr_desktop.x + curr_desktop.dx * (curr_keybind.window_pos[0]),
		curr_desktop.y + curr_desktop.dy * (curr_keybind.window_pos[1]),
		curr_desktop.dx * (curr_keybind.window_pos[2] - curr_keybind.window_pos[0]),
		curr_desktop.dy * (curr_keybind.window_pos[3] - curr_keybind.window_pos[1]));
}

void do_shortcut(char c, int window)
{
	struct screen_sizes desktop_sizes = get_desktop_sizes();
	struct screen_size window_size = get_window_size();
	struct keybind_arr keybinds = read_keybinds("data/keybinds");

	struct screen_size curr_desktop;
	if (window == -1)
	{
		curr_desktop = desktop_sizes.arr[get_current_window(desktop_sizes, window_size)];
	}
	else
	{
		curr_desktop = desktop_sizes.arr[window - 1];
	}

	for (int i = 0; i < keybinds.len; i++)
	{
		if (keybinds.arr[i].escape_char == c)
		{
			if (keybinds.arr[i].is_cursor_swap)
			{
				panic("Unimplmented");
			}
			else
			{
				do_resize(curr_desktop, keybinds.arr[i]);
			}
		}
	}
}