#include "shell.h"

/**
 * verifier_builtin - checks if the command is a builtin
 * @args: array of arguments
 * @ligne: the original line to free
 * Return: 1 if it was a builtin, 0 otherwise
 */
int verifier_builtin(char **args, char *ligne)
{
	if (strcmp(args[0], "exit") == 0)
	{
		liberer_grille(args);
		free(ligne);
		exit(0);
	}
	return (0);
}
