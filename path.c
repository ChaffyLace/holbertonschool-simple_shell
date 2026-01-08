#include "shell.h"

/**
 * direct_path - check absolute or relative path
 * @cmd: command array
 *
 * Return: 1 if executable, -1 if not executable,
 *         -2 if directory, 0 if not found
 */
int direct_path(char **cmd)
{
	struct stat st;

	if (stat(cmd[0], &st) == 0 && S_ISDIR(st.st_mode))
		return (-2);

	if (access(cmd[0], F_OK) != 0)
		return (0);

	if (access(cmd[0], X_OK) != 0)
		return (-1);

	return (1);
}

/**
 * get_path - find command in PATH and replace cmd[0]
 * @cmd: command array
 *
 * Return: 1 if found and executable, 0 otherwise
 */
int get_path(char **cmd)
{
	char *env, *path, *dir, *full;

	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		return (0);

	/* Absolute or relative path */
	if (cmd[0][0] == '/' ||
	    (cmd[0][0] == '.' && cmd[0][1] == '/') ||
	    (cmd[0][0] == '.' && cmd[0][1] == '.' && cmd[0][2] == '/'))
		return (direct_path(cmd));

	env = _getenv("PATH");
	if (!env)
		return (0);

	path = _strdup(env + 5);
	if (!path)
		return (0);

	dir = strtok(path, ":");
	while (dir)
	{
		full = malloc(_strlen(dir) + _strlen(cmd[0]) + 2);
		if (!full)
			break;

		_strcpy(full, dir);
		_strcat(full, "/");
		_strcat(full, cmd[0]);

		if (access(full, F_OK) == 0)
		{
			free(path);
			free(cmd[0]);
			cmd[0] = full;

			if (access(full, X_OK) != 0)
				return (-1);

			return (1);
		}

		free(full);
		dir = strtok(NULL, ":");
	}

	free(path);
	return (0);
}
