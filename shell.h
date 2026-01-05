#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

void execute_command(char **args, char *input, char *name, int count);
char **split_line(char *line);
void free_array(char **arr);

#endif
