#include "shell.h"

/**
 * env_builtin - handle env built-in
 * @cmd: command arguments
 *
 * Return: 1 if env executed, 0 otherwise
 */
int env_builtin(char **cmd)
{
	int i = 0, j;

	if (!cmd || !cmd[0])
		return (0);

	if (_strcmp(cmd[0], "env") == 0 && cmd[1] == NULL)
	{
		while (environ[i])
		{
			j = 0;
			while (environ[i][j])
			{
				_putchar(environ[i][j]);
				j++;
			}
			_putchar('\n');
			i++;
		}
		return (1);
	}

	return (0);
}

/**
 * exit_builtin - handle exit built-in
 * @cmd: command arguments
 * @prog: program name (argv[0])
 * @line: line number
 *
 * Return: 1 if exit error, 0 otherwise
 */
int exit_builtin(char **cmd, char *prog, unsigned int line)
{
	int status;

	if (!cmd || !cmd[0])
		return (0);

	if (_strcmp(cmd[0], "exit") != 0)
		return (0);

	if (!cmd[1])
	{
		free_cmd(cmd);
		exit(0);
	}

	if (!_isnumber(cmd[1]))
	{
		print_exit_illegal(prog, line, cmd[1]);
		free_cmd(cmd);
		exit(2);
	}

	if (cmd[2])
	{
		print_exit_too_many(prog, line);
		return (1);
	}

	status = _atoi(cmd[1]) % 256;
	if (status < 0)
		status += 256;

	free_cmd(cmd);
	exit(status);
}
