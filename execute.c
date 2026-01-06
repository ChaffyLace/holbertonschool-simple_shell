#include "shell.h"

/**
 * execute_command - fork and execute a command
 * @args: arguments array
 * @line: input line
 * @name: program name (argv[0])
 * @count: command counter
 */
void execute_command(char **args, char *line, char *name, int count)
{
	pid_t pid;
	int status;
	char *cmd_path = NULL;

	(void)line;

	if (strchr(args[0], '/'))
		cmd_path = strdup(args[0]);
	else
		cmd_path = find_path(args[0]);

	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			name, count, args[0]);
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
