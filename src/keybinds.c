#include "keybinds.h"

struct keybind_arr read_keybinds(char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "Couldnt open file %s\n", filename);
		exit(1);
	}

	char* content = readfile(fp);

	int lines = 0;
	for (int i = 0; i < strlen(content); i++) {
		if (content[i] == '\n')
			lines += 1;
	}

	struct keybind_arr ret = {
		.arr = malloc(sizeof(struct keybind) * lines),
		.len = lines
	};

	char* token = strtok(content, "\n");

	for (int i = 0; i < lines; i++) {
		struct keybind* curr = &ret.arr[i];
		sscanf(token, "%c:%f,%f,%f,%f", &(curr -> escape_char),
				&(curr -> window_pos[0]), &(curr -> window_pos[1]),
				&(curr -> window_pos[2]), &(curr -> window_pos[3]));

		token = strtok(NULL, "\n");
	}

	fclose(fp);
	free(content);
	return ret;
}
