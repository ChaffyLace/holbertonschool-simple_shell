#include "shell.h"

/**
 * split_line - split input line into arguments
 * @line: input line
 * Return: NULL-terminated array of strings
 */
char **split_line(char *line)
{
	char **args;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);

	token = strtok(line, " \n\t");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " \n\t");
	}
	args[i] = NULL;
	return (args);
}

/**
 * main - Simple shell 0.1 +
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	char **args;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		if (read > 1)
		{
			args = split_line(line);
			if (!args || !args[0])
				continue;

			pid = fork();
			if (pid == 0)
			{
				execve(args[0], args, environ);
				perror("./shell");
				exit(EXIT_FAILURE);
			}
			else
			{
				wait(NULL);
			}

			free(args);
		}
	}

	free(line);
	return (0);
}
