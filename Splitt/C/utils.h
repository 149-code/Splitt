#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

char* readfile(FILE* fp);
char* get_home_dir(void);
char* path_join(char* s1, char* s2);

#endif
