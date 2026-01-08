#include "shell.h"

/**
 * executer - execute a command
 * @args: array of arguments
 * @nom_prog: program name
 * @n_ligne: line number
 * Return: exit status
 */
int executer(char **args, char *nom_prog, int n_ligne)
{
	pid_t pid;
	int status = 0;
	char *chemin = NULL;
	struct stat st;

	if (strchr(args[0], '/') != NULL)
	{
		if (stat(args[0], &st) == 0)
			chemin = strdup(args[0]);
	}
	else
		chemin = chercher_chemin(args[0]);
	if (!chemin)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			nom_prog, n_ligne, args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(chemin, args, environ) == -1)
		{
			perror(nom_prog);
			free(chemin);
			liberer_grille(args);
			exit(127);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	else
		perror("fork");
	if (chemin != args[0])
		free(chemin);
	return (status);
}
