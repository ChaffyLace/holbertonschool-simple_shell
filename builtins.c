#include "shell.h"

/**
 * verifier_builtins - check for exit and env
 * @args: arguments
 * @ligne: buffer
 * Return: 1 if builtin, 0 if not
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
