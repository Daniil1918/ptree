#ifndef H_UTILS
#define H_UTILS

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MIN_LEN 256
#define MAX_LEN 2048
#define INDENT "    "

int8_t *presence_pid;

typedef struct dirent dirent_t;

void build_tree(pid_t root_pid, u_int32_t count_indent);
void print_line(pid_t pid);

#endif
