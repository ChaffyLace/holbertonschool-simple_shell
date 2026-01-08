#ifndef SHELL_H_
#define SHELL_H_
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;
int _putchar(char c);
void _puts(char *str);
int _strcmp(char *s1, char *s2);
char *_strndup(char *str, int n);
int _strlen(char *str);
char *_strcat(char *dest, char *src);
char **strtow(char *str);
void free_cmd(char **str);
int _strncmp(char *s1, char *s2, unsigned int n);
char *_getenv(char *name);
char *_strdup(char *str);
int get_path(char **cmd);
int execve_cmd(char **cmd, char *prog, unsigned int line);
void *_calloc(unsigned int nmemb, unsigned int size);
char *_memset(char *s, char b, unsigned int n);
void print_not_found(char *prog, unsigned int line, char *cmd);
void print_perm_denied(char *prog, unsigned int line, char *cmd);
void print_is_dir(char *prog, unsigned int line, char *cmd);
void print_exit_illegal(char *prog, unsigned int line, char *arg);
void print_exit_too_many(char *prog, unsigned int line);
int direct_path(char **cmd);
int env_builtin(char **cmd);
int exit_builtin(char **cmd, char *prog, unsigned int line);
int _isdigit(int d);
int _isnumber(char *str);
int _atoi(char *s);

#endif
