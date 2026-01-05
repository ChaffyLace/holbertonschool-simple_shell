#include "shell.h"

void execute_command(char **args, char *input, char *name, int count)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", name, count, args[0]);
			free(input);
			free_array(args);
			exit(127);
		}
	}
	else if (pid < 0)
	{
		perror("Fork failed");
	}
	else
	{
		wait(&status);
	}
}
