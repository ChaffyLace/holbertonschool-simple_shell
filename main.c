#include "shell.h"

/**
 * main - main loop of the shell
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	char *ligne = NULL;
	size_t taille = 0;
	ssize_t n_lus;
	char **arguments;
	int compteur = 0;
	(void)ac;

	while (1)
	{
		compteur++;
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

		arguments = decouper_ligne(ligne);
		if (arguments && arguments[0])
		{
			if (strcmp(arguments[0], "exit") == 0)
			{
				liberer_grille(arguments);
				break;
			}
			executer(arguments, av[0], compteur);
		}
		liberer_grille(arguments);
	}
	free(ligne);
	return (0);
}
