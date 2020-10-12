#include "utils.h"

char* get_home_dir()
{
        struct passwd *pw = getpwuid(getuid());
        return pw -> pw_dir;
}

char* readfile(FILE* fp)
{
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

char* path_join(char* s1, char* s2)
{
        int len1 = (int) strlen(s1);
        int len2 = (int) strlen(s2);
        
        char* ret = malloc(len1 + len2 + 2);
        memcpy(ret, s1, len1);
        ret[len1] = '/';
        memcpy(ret + len1 + 1, s2, len2);
        ret[len1 + len2 + 1] = '\0';
        
        return ret;
}
