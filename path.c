#include "shell.h"

/**
 * find_path - finds full path of a command
 * @cmd: command name
 *
 * Return: full path or NULL
 */
char *find_path(char *cmd)
{
	char *path, *path_copy, *dir, *full_path;
	struct stat st;

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, cmd);

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
