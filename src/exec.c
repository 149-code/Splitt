#include "exec.h"

struct screen_sizes get_desktop_sizes()
{
	FILE* proc = popen("cat scripts/desktop_size.script | osascript", "r");
	if (proc == NULL) {
		fprintf(stderr, "Something went wrong :(");
		exit(1);
	}

	char* output = readfile(proc);

	int num_windows = 1;
	for (int i = 0; i < strlen(output); i++) {
		if (output[i] == ' ') {
			num_windows ++;
		}
	}

	num_windows = num_windows / 4;
	struct screen_sizes ret = {malloc(sizeof(struct screen_size) * num_windows), num_windows};
	char* output_cpy = output;
	float buffer[4];

	for (int i = 0; i < num_windows; i++) {
		output_cpy += sscanf(output_cpy, "%f %f %f %f",
				buffer, buffer + 1, buffer + 2, buffer + 3) + 1;
		ret.arr[i] = (struct screen_size) {
			.x = buffer[0],
			.y = buffer[1],
			.dx = buffer[2] - buffer[0],
			.dy = buffer[3] - buffer[1],
		};
	}

	free(output);
	pclose(proc);

	return ret;
}

struct screen_size get_window_size()
{
	FILE* proc = popen("cat scripts/window_size.script | osascript", "r");
	if (proc == NULL) {
		fprintf(stderr, "Something went wrong :(");
		exit(1);
	}

	char* output = readfile(proc);
	float buffer[4];

	sscanf(output, "%f %f %f %f", buffer, buffer + 1,
			buffer + 2, buffer + 3);

	free(output);
	pclose(proc);

	return (struct screen_size) {
		.x = buffer[0],
		.y = buffer[1], 
		.dx = buffer[2] - buffer[0],
		.dy = buffer[3] - buffer[1],
	};
}

void resize_current_window(int p1, int p2, int p3, int p4)
{
	FILE* fp = fopen("scripts/resize.script", "r");
	if (fp == NULL) {
		fprintf(stderr, "Couldn't open resize.script");
		exit(1);
	}

	char* script = readfile(fp);
	char* format_buffer1 = malloc(strlen(script) + 100);
	char* format_buffer2 = malloc(strlen(script) + 100);

	sprintf(format_buffer1, script, p1, p2, p3, p4);
	sprintf(format_buffer2, "echo '%s' | osascript", format_buffer1);

	popen(format_buffer2, "r");

	free(script);
	free(format_buffer1);
	free(format_buffer2);
	fclose(fp);
}
