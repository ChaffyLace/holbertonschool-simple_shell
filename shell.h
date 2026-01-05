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

void exec_cmd(char **args, char *input, char *prog_name, int count);
char **parse_input(char *input);
void free_args(char **args);

#endif
