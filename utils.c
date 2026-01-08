#include "shell.h"

/**
 * decouper_ligne - split string
 * @ligne: input
 * Return: array of strings
 */
char **decouper_ligne(char *ligne)
{
	char **tokens;
	char *t;
	int i = 0;

	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
		return (NULL);
	t = strtok(ligne, " \t\r\n\a");
	while (t)
	{
		tokens[i] = strdup(t);
		i++;
		t = strtok(NULL, " \t\r\n\a");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * liberer_grille - free pointer array
 * @grille: array
 */
void liberer_grille(char **grille)
{
	int i = 0;

	if (!grille)
		return;
	while (grille[i])
	{
		free(grille[i]);
		i++;
	}
	free(grille);
}
