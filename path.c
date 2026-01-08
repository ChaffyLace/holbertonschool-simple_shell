#include "shell.h"

/**
 * _getenv - find variable
 * @nom: name
 * Return: value
 */
char *_getenv(char *nom)
{
	int i = 0;
	int len = strlen(nom);

	while (environ && environ[i])
	{
		if (strncmp(environ[i], nom, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * chercher_chemin - search in PATH
 * @commande: command
 * Return: path
 */
char *chercher_chemin(char *commande)
{
	char *path_env, *copie, *dossier, *complet;
	struct stat st;

	path_env = _getenv("PATH");
	if (!path_env || strlen(path_env) == 0)
		return (NULL);

	copie = strdup(path_env);
	dossier = strtok(copie, ":");
	while (dossier)
	{
		complet = malloc(strlen(dossier) + strlen(commande) + 2);
		strcpy(complet, dossier);
		strcat(complet, "/");
		strcat(complet, commande);

		if (stat(complet, &st) == 0)
		{
			free(copie);
			return (complet);
		}
		free(complet);
		dossier = strtok(NULL, ":");
	}
	free(copie);
	return (NULL);
}
