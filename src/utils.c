#include "utils.h"

char* readfile(FILE* fp) {
	char* ret = malloc(0);
	int size = 0;
	char c;

	while ((c = fgetc(fp)) != EOF) {
		ret = realloc(ret, size + 1);
		ret[size++] = c;
	}

	ret = realloc(ret, size + 1);
	ret[size] = '\0';

	return ret;
}