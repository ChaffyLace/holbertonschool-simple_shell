#include "shell.h"

/**
 * verifier_builtins - exit and env
 * @args: args
 * @ligne: buffer
 * Return: 1 or 0
 */
int verifier_builtins(char **args, char *ligne)
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
