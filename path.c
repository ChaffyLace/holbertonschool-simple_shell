#include "shell.h"

char *find_path(char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy;
	char *dir;
	char *full_path;
	struct stat st;

	if (!path)
		return (NULL);

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
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
