#include "shell.h"

/**
 * get_full_path - Trouve le chemin complet d'une commande
 * @command: Nom de la commande
 * Return: Chemin complet ou NULL
 */
char *get_full_path(char *command)
{
	char *path_env = NULL;
	char *path_copy, *dir, *full_path;
	struct stat st;
	int i = 0;

	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}
	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path_env = environ[i] + 5;
			break;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	path_copy = strdup(path_env);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		sprintf(full_path, "%s/%s", dir, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
