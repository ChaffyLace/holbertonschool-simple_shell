#include "shell.h"

/**
 * verifier_builtin - checks if the command is a builtin
 * @args: array of arguments
 * @ligne: the original line to free
 * Return: 1 if it was a builtin, 0 otherwise
 */
int verifier_builtin(char **args, char *ligne)
{
	int i;

	if (strcmp(args[0], "exit") == 0)
	{
		liberer_grille(args);
		free(ligne);
		exit(0);
	}

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (1);
	}
	return (0);
}
