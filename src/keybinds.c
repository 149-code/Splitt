#include "keybinds.h"
#include "utils.h"

struct keybind_arr read_keybinds(char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "Couldn't open keybinds file: %s", filename);
		exit(1);
	}
	char* content = readfile(fp);

	int num_splits = 0;
	for (int i = 0; i < strlen(content); i++) {
		if (content[i] == '\n') {
			num_splits ++;
		}
	}

	struct keybind_arr ret = {
		.arr = malloc(num_splits * sizeof(struct keybind)),
		.len = num_splits
	};

	int slice_num = 0;
	int i = 0;
	int* slices = malloc(sizeof(int) * num_splits);

	while (slice_num < num_splits) {
		if (content[i] == '\n') {
			content[i] = '\0';
			slices[slice_num + 1] = i + 1;
			slice_num ++;
		}
		i ++;
	}

	for (int i = 0; i < num_splits; i++) {
		struct keybind* ptr = ret.arr + i;
		sscanf(&content[slices[i]], "%c: %f, %f, %f, %f", &ptr -> escape_char,
				ptr -> window_pos, ptr -> window_pos + 1,
				ptr -> window_pos + 2, ptr -> window_pos + 3);
	}

	free(content);
	return ret;
}
