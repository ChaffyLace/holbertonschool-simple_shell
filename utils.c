#include "shell.h"

/**
 * decouper_ligne - splits the input line into tokens
 * @ligne: raw string input
 * Return: array of tokens
 */
char **decouper_ligne(char *ligne)
{
	char **tokens;
	char *t;
	int i = 0;

	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
		return (NULL);

	t = strtok(ligne, " \t\r\n");
	while (t)
	{
		tokens[i] = strdup(t);
		i++;
		t = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * liberer_grille - frees the memory of an array
 * @grille: array of pointers
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
