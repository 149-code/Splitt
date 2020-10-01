#include "exec.h"
#include "utils.h"

struct screen_sizes get_desktop_size() {
	FILE* proc = popen("cat scripts/desktop_size.script | osascript", "r");
	if (proc == NULL) {
		fprintf(stderr, "Something went wrong :(");
		exit(1);
	}
	char* output = readfile(proc);

	int nums = 1;
	for (int i = 0; i < strlen(output); i++) {
		if (output[i] == ' ') {
			nums ++;
		}
	}

	struct screen_sizes ret = {nums / 4, malloc(nums * sizeof(int))};

	char buffer[8]; // Hopefully there screen isnt't bigger then 10 mil pixels
	int buffer_len = 0;
	int current_num = 0;

	for (int i = 0; i < strlen(output); i++) {
		if (output[i] == ' ') {
			ret.sizes[current_num++] = atoi(buffer);
			memset(buffer, 0, 8);
			buffer_len = 0;
		} else {
			buffer[buffer_len++] = output[i];
		}
	}

	ret.sizes[current_num++] = atoi(buffer);

	free(output);
	return ret;
}

struct screen_sizes get_window_size() {
	FILE* proc = popen("cat scripts/screen_size.script | osascript", "r");
	if (proc == NULL) {
		fprintf(stderr, "Something went wrong :(");
		exit(1);
	}
	char* output = readfile(proc);

	struct screen_sizes ret = {1, malloc(4 * sizeof(int))};

	sscanf(output, "%d %d %d %d", ret.sizes, ret.sizes + 1,
			ret.sizes + 2, ret.sizes + 3);

	free(output);
	return ret;
}

void resize_current_window(int p1, int p2, int p3, int p4) {
	FILE* fp = fopen("scripts/resize.script", "r");
	char* script = readfile(fp);
	char* format_buffer1 = malloc(strlen(script) + 100);
	char* format_buffer2 = malloc(strlen(script) + 100);

	sprintf(format_buffer1, script, p1, p2, p3, p4);
	sprintf(format_buffer2, "echo '%s' | osascript", format_buffer1);

	popen(format_buffer2, "r");

	free(script);
	free(format_buffer1);
	free(format_buffer2);
}
