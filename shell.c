#include "shell.h"

/**
 * ctrlC - function called by signal
 * @signal: unused
 * Description: ctrlC cancel the current line and produce new prompt
 * Return: void
 */
void ctrlC(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * handle_cmd - handle one parsed command (builtins + path + exec/errors)
 * @cmd: command array
 * @av: argv from main
 * @line: current line number
 * Return: exit status
 */
static int handle_cmd(char **cmd, char **av, unsigned int line)
{
	int path_value;

	if (env_builtin(cmd) || exit_builtin(cmd, av[0], line))
		return (0);

	path_value = get_path(cmd);

	if (path_value == 1)
		return (execve_cmd(cmd, av[0], line));

	if (path_value == -2)
		return (print_is_dir(av[0], line, cmd[0]), 126);

	if (path_value == -1)
		return (print_perm_denied(av[0], line, cmd[0]), 126);

	print_not_found(av[0], line, cmd[0]);
	return (127);
}

/**
 * main - Entry
 * @ac: ac
 * @av: av
 * Description: main function that run getline to read from the terminal
 * split the command from input
 * compare the input to built-ins commands
 * send the command to getpath to form a valid path
 * Return: 0
 */
int main(int ac, char **av)
{
	char *buffer = NULL;
	char **cmd = NULL;
	size_t b_size = 0;
	int user = isatty(STDIN_FILENO);
	unsigned int line = 0;
	int status = 0;

	(void)ac;

	signal(SIGINT, ctrlC);

	if (user)
		_puts("$ ");

	while (getline(&buffer, &b_size, stdin) != -1 && ++line)
	{
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

		if (user)
			_puts("$ ");
	}

	if (user)
		putchar('\n');

	free(buffer);
	return (status);
}
