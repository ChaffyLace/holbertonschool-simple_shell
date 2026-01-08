#include "shell.h"

/**
 * executer - execute a command
 * @args: array of arguments
 * @nom_prog: program name for errors
 * @n_ligne: line number for errors
 */
void executer(char **args, char *nom_prog, int n_ligne)
{
	pid_t pid;
	int status;
	char *chemin;
	struct stat st;

	if (stat(args[0], &st) == 0)
		chemin = args[0];
	else
	{
		chemin = chercher_chemin(args[0]);
		if (!chemin)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				nom_prog, n_ligne, args[0]);
			return;
		}
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(chemin, args, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else if (pid > 0)
		wait(&status);
	else
		perror("fork");

	if (chemin != args[0])
		free(chemin);
}
