#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

char **split_line(char *line);
void free_array(char **arr);
char *_getenv(const char *name);
char *find_path(char *cmd);
void execute_command(char **args, char *name, int count);

#endif
