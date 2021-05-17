#include "logic.h"

int get_current_space_application(struct screen_infos desktop_infos, struct screen_size window)
{
	for (int i = 0; i < desktop_infos.len; i++)
	{
		struct screen_size curr = desktop_infos.arr[i].size;
		if (curr.x <= window.x && curr.y <= window.y &&
			curr.x + curr.dx >= window.x + window.dx &&
			curr.x + curr.dx >= window.x + window.dx)
		{
			return i;
		}
	}

	return -1;
}

int get_current_space_cursor(struct screen_infos desktop_infos, CGPoint cursor_pos)
{
	for (int i = 0; i < desktop_infos.len; i++)
	{
		struct screen_size curr = desktop_infos.arr[i].size;

		if (curr.x <= cursor_pos.x && curr.y <= cursor_pos.y &&
			cursor_pos.x <= curr.x + curr.dx && cursor_pos.y <= curr.y + curr.dy)
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
	struct screen_infos desktop_info = get_desktop_sizes();
	struct screen_size window_size = get_window_size();
	struct keybind_arr keybinds = read_keybinds("data/keybinds");

	for (int i = 0; i < keybinds.len; i++)
	{
		if (keybinds.arr[i].escape_char == c)
		{
			if (keybinds.arr[i].is_cursor_swap)
			{
				CGPoint cursor_pos = get_cursor_pos();
				int curr_window = get_current_space_cursor(desktop_info, cursor_pos);

				int target_window;
				if (window == -1)
					target_window = (curr_window + 1) % desktop_info.len;
				else
					target_window = window - 1;

				CGPoint cursor_rel_to_curr_win = {
					.x = (cursor_pos.x - desktop_info.arr[curr_window].size.x) /
					     desktop_info.arr[curr_window].size.dx,
					.y = (cursor_pos.y - desktop_info.arr[curr_window].size.y) /
					     desktop_info.arr[curr_window].size.dy,
				};

				CGPoint cursor_rel_to_new_win = {
					.x = cursor_rel_to_curr_win.x *
					     desktop_info.arr[target_window].size.dx,
					.y = cursor_rel_to_curr_win.y *
					     desktop_info.arr[target_window].size.dy,
				};

				CGDisplayMoveCursorToPoint(
					desktop_info.arr[target_window].id, cursor_rel_to_new_win);
			}
			else
			{
				int curr_window =
					get_current_space_application(desktop_info, window_size);

				struct screen_size curr_desktop_size;
				if (window == -1)
					curr_desktop_size = desktop_info.arr[curr_window].size;
				else
					curr_desktop_size = desktop_info.arr[window - 1].size;

				do_resize(curr_desktop_size, keybinds.arr[i]);
			}
		}
	}
}
