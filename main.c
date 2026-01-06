#include "shell.h"

/**
 * main - shell main loop
 * @ac: arg count
 * @av: arg vector
 * Return: 0
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

		arguments = decouper_ligne(ligne);
		if (arguments && arguments[0])
		{
			if (verifier_builtin(arguments, ligne))
				continue;
			
			executer(arguments, av[0], compteur);
		}
		liberer_grille(arguments);
	}
	free(ligne);
	return (0);
}
