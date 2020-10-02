#include <stdio.h>
#include "keybinds.h"

int main()
{
	struct keybind_arr keybinds = read_keybinds("keybinds");
	for (int i = 0; i < keybinds.len; i++) {
		printf("%c\n", keybinds.arr[i].escape_char);
	}
}
