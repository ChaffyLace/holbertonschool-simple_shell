#include "shell.h"

/**
 * main - Simple shell 0.1
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	char *argv[2];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (*line == '\0')
			continue;

		argv[0] = line;
		argv[1] = NULL;

		pid = fork();
		if (pid == 0)
		{
			execve(argv[0], argv, environ);
			perror("./shell");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}

	free(line);
	return (0);
}
