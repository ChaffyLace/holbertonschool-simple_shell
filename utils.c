#include "shell.h"

/**
 * decouper_ligne - splits string into tokens
 * @ligne: string input
 * Return: tokens array
 */
char **decouper_ligne(char *ligne)
{
	char **tokens;
	char *t;
	int i = 0;

	if (!ligne)
		return (NULL);
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
 * liberer_grille - frees double pointer array
 * @grille: array to free
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
