#include "shell.h"

/**
 * handle_builtin - Gère les commandes internes
 * @args: Liste des arguments
 * Return: 1 si commande gérée, 0 sinon
 */
int handle_builtin(char **args)
{
	int i = 0;

	if (strcmp(args[0], "exit") == 0)
	{
		free_args(args);
		exit(0);
	}

	if (strcmp(args[0], "env") == 0)
	{
		while (environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
		free_args(args);
		return (1);
	}

	return (0);
}
