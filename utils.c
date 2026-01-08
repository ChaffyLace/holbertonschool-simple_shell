#include "shell.h"

/**
 * decouper_ligne - split line into words
 * @ligne: raw line
 * Return: array of words
 */
char **decouper_ligne(char *ligne)
{
	char **mots;
	char *morceau;
	int i = 0;

	mots = malloc(sizeof(char *) * 1024);
	if (!mots)
		return (NULL);

	morceau = strtok(ligne, " \t\n");
	while (morceau)
	{
		mots[i] = strdup(morceau);
		i++;
		morceau = strtok(NULL, " \t\n");
	}
	mots[i] = NULL;
	return (mots);
}

/**
 * liberer_grille - free the array
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
