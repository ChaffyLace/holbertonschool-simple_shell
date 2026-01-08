#include "shell.h"

/**
 * main - Point d'entrée du shell simple
 * Return: Toujours 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **argv;
	char *token;
	int i;
	int status;
	char *cmd_path;
	pid_t child_pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			exit(0);
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		argv = malloc(sizeof(char *) * 64);
		if (!argv)
			continue;
		i = 0;
		token = strtok(line, " ");
		while (token != NULL)
		{
			argv[i++] = strdup(token);
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;
		if (argv[0] == NULL)
		{
			free(argv);
			continue;
		}
		if (handle_builtin(argv))
			continue;
		cmd_path = get_full_path(argv[0]);
		if (cmd_path == NULL)
		{
			perror("./hsh");
			free_args(argv);
			continue;
		}
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(cmd_path, argv, environ) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		else
			wait(&status);
		if (strcmp(cmd_path, argv[0]) != 0)
			free(cmd_path);
		free_args(argv);
	}
	free(line);
	return (0);
}
