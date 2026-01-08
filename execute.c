#include "shell.h"

/**
 * executer_commande - run command
 * @arguments: args
 * @nom_shell: shell name
 * @n_ligne: line count
 */
void executer_commande(char **arguments, char *nom_shell, int n_ligne)
{
	char *chemin_final = NULL;
	pid_t mon_pid;
	int statut;

	if (arguments[0][0] == '/' || arguments[0][0] == '.')
		chemin_final = strdup(arguments[0]);
	else
		chemin_final = trouver_chemin(arguments[0]);

	if (chemin_final == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", nom_shell, n_ligne, arguments[0]);
		return;
	}

	mon_pid = fork();
	if (mon_pid == 0)
	{
		if (execve(chemin_final, arguments, environ) == -1)
		{
			perror(nom_shell);
			free(chemin_final);
			exit(127);
		}
	}
	else
	{
		wait(&statut);
	}
	free(chemin_final);
}
