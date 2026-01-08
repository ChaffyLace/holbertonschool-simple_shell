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

char **decouper_ligne(char *ligne);
void liberer_grille(char **grille);
char *_getenv(char *nom);
char *trouver_chemin(char *commande);
void executer_commande(char **arguments, char *nom_shell, int n_ligne);
int verifier_builtins(char **args, char *ligne);

#endif
