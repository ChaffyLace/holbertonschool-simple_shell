#include "shell.h"

/**
 * trouver_variable - looks for an environment variable
 * @nom: variable name
 * Return: value or NULL if not found
 */
char *trouver_variable(const char *nom)
{
	int i, longueur;

	if (nom == NULL || environ == NULL)
		return (NULL);

	longueur = strlen(nom);
	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], nom, longueur) == 0 &&
		    environ[i][longueur] == '=')
			return (environ[i] + longueur + 1);
	}
	return (NULL);
}

/**
 * chercher_chemin - builds the full path of a command
 * @commande: name of the command
 * Return: full path or NULL
 */
char *chercher_chemin(char *commande)
{
	char *path, *copie_path, *dossier, *complet;
	struct stat st;

	path = trouver_variable("PATH");
	if (!path || strlen(path) == 0)
		return (NULL);

	copie_path = strdup(path);
	dossier = strtok(copie_path, ":");
	while (dossier)
	{
		complet = malloc(strlen(dossier) + strlen(commande) + 2);
		if (!complet)
		{
			free(copie_path);
			return (NULL);
		}
		strcpy(complet, dossier);
		strcat(complet, "/");
		strcat(complet, commande);

		if (stat(complet, &st) == 0)
		{
			free(copie_path);
			return (complet);
		}
		free(complet);
		dossier = strtok(NULL, ":");
	}
	free(copie_path);
	return (NULL);
}
