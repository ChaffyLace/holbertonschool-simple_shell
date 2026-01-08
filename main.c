#include "shell.h"

/**
 * main - simple shell loop
 * @ac: arg count
 * @av: arg vector
 * Return: exit status
 */
int main(int ac, char **av)
{
	char *ligne = NULL;
	size_t taille = 0;
	ssize_t n_lus;
	char **args;
	int cpt = 0;
	int status = 0;

	(void)ac;
	while (1)
	{
		cpt++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		n_lus = getline(&ligne, &taille, stdin);
		if (n_lus == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (ligne[n_lus - 1] == '\n')
			ligne[n_lus - 1] = '\0';
		args = decouper_ligne(ligne);
		if (args && args[0])
		{
			if (verifier_builtin(args, ligne, status))
				continue;
			status = executer(args, av[0], cpt);
		}
		liberer_grille(args);
	}
	free(ligne);
	return (status);
}
