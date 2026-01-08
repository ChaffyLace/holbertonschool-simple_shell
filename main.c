#include "shell.h"

/**
 * ctrlC - handle Ctrl+C
 * @sig: unused
 */
void ctrlC(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}

int main(int ac, char **av)
{
	char *buffer = NULL;
	char **cmd = NULL;
	size_t size = 0;
	unsigned int line = 0;
	int interactive;
	int status = 0;

	(void)ac;
	signal(SIGINT, ctrlC);
	interactive = isatty(STDIN_FILENO);

	if (interactive)
		write(STDOUT_FILENO, "$ ", 2);

	while (getline(&buffer, &size, stdin) != -1)
	{
		line++;
		cmd = strtow(buffer);
		if (cmd && cmd[0] && _strcmp(cmd[0], "exit") == 0 && !cmd[1])
		{
			free_cmd(cmd);
			free(buffer);
			exit(status);
		}
		if (cmd)
		{
			status = handle_cmd(cmd, av, line);
			free_cmd(cmd);
		}
		if (interactive)
			write(STDOUT_FILENO, "$ ", 2);
	}

	if (interactive)
		write(STDOUT_FILENO, "\n", 1);

	free(buffer);
	return (status);
}
