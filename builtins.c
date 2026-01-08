#include "shell.h"

/**
 * verifier_builtin - check for exit or env
 * @args: arguments
 * @ligne: buffer to free
 * @status: exit status
 * Return: 1 if builtin, 0 if not
 */
int verifier_builtin(char **args, char *ligne, int status)
{
	int i;

	if (strcmp(args[0], "exit") == 0)
	{
		liberer_grille(args);
		free(ligne);
		exit(status);
	}
	if (strcmp(args[0], "env") == 0)
	{
		if (!environ)
			return (1);
		for (i = 0; environ[i]; i++)
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		liberer_grille(args);
		return (1);
	}
	return (0);
}
