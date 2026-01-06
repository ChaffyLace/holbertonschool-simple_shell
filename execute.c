#include "shell.h"

/**
 * execute_command - forks and runs the command
 * @args: arguments
 * @name: shell name
 * @count: line count
 */
void execute_command(char **args, char *name, int count)
{
	char *cmd_path = NULL;
	pid_t pid;
	int status;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (access(args[0], X_OK) == 0)
			cmd_path = strdup(args[0]);
	}
	else
	{
		cmd_path = find_path(args[0]);
	}

	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", name, count, args[0]);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror(name);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
	free(cmd_path);
}
