#include "shell.h"

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
			free(line);
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		args = split_line(line);
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free_array(args);
				free(line);
				exit(0);
			}
			execute_command(args, line, av[0], count);
		}
		free_array(args);
	}
	return (0);
}
