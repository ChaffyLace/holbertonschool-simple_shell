#include "shell.h"

/**
 * executer - handles fork and execution
 * @args: list of arguments
 * @nom_prog: name of the shell program
 * @n_ligne: line number for error display
 */
void executer(char **args, char *nom_prog, int n_ligne)
{
	char *chemin = NULL;
	pid_t enfant_pid;
	int etat;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (access(args[0], X_OK) == 0)
			chemin = strdup(args[0]);
	}
	else
		chemin = chercher_chemin(args[0]);

	if (!chemin)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			nom_prog, n_ligne, args[0]);
		return;
	}

	enfant_pid = fork();
	if (enfant_pid == 0)
	{
		if (execve(chemin, args, environ) == -1)
		{
			perror(nom_prog);
			exit(127);
		}
	}
	else
		wait(&etat);

	free(chemin);
}
