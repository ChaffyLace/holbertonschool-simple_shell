#include "shell.h"

/**
 * _getenv - finds an environment variable
 * @name: variable name
 * Return: value string
 */
char *_getenv(const char *name)
{
	int i, len;

	len = strlen(name);
	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

/**
 * find_path - finds the full path for a command
 * @cmd: command name
 * Return: full path or NULL
 */
char *find_path(char *cmd)
{
	char *path, *path_cp, *dir, *full;
	struct stat st;

	path = _getenv("PATH");
	if (!path || strlen(path) == 0)
		return (NULL);

	path_cp = strdup(path);
	dir = strtok(path_cp, ":");
	while (dir)
	{
		full = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full)
			return (NULL);
		strcpy(full, dir);
		strcat(full, "/");
		strcat(full, cmd);

		if (stat(full, &st) == 0)
		{
			free(path_cp);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(path_cp);
	return (NULL);
}
