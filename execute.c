#include "shell.h"

/**
 * executer - execute command
 * @args: arguments
 * @nom_prog: argv[0]
 * @n_ligne: counter
 */
void executer(char **args, char *nom_prog, int n_ligne)
{
	char *chemin = NULL;
	pid_t pid;
	int status;

	if (args[0][0] == '/' || args[0][0] == '.')
		chemin = strdup(args[0]);
	else
		chemin = chercher_chemin(args[0]);

	if (!chemin)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", nom_prog, n_ligne, args[0]);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(chemin, args, environ) == -1)
		{
			perror(nom_prog);
			free(chemin);
			exit(127);
		}
	}
	else
		wait(&status);
	free(chemin);
}
