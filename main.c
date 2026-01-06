#include "shell.h"

/**
 * main - entry point of the shell
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int count = 0;

	(void)ac;

	while (1)
	{
		count++;

		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		args = split_line(line);
		if (args && args[0])
			execute_command(args, line, av[0], count);

		free_array(args);
	}

	free(line);
	return (0);
}
