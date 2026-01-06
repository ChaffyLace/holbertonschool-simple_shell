#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

char **split_line(char *line);
void free_array(char **arr);
char *find_path(char *cmd);
void execute_command(char **args, char *line, char *name, int count);

#endif
