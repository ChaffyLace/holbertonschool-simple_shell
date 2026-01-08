#include "shell.h"

/**
 * _getenv - find variable in env
 * @name: name of variable
 * Return: value after '=' or NULL
 */
char *_getenv(char *name)
{
	int i = 0;
	int nlen;

	if (!name || !environ)
		return (NULL);

	nlen = strlen(name);
	while (environ[i])
	{
		if (strncmp(environ[i], name, nlen) == 0 && environ[i][nlen] == '=')
			return (environ[i] + nlen + 1);
		i++;
	}
	return (NULL);
}

/**
 * chercher_chemin - finds command path
 * @commande: command name
 * Return: full path or NULL
 */
char *chercher_chemin(char *commande)
{
	char *path, *copie, *dossier, *complet;
	struct stat st;

	path = _getenv("PATH");
	if (!path || strlen(path) == 0)
		return (NULL);

	copie = strdup(path);
	dossier = strtok(copie, ":");
	while (dossier)
	{
		complet = malloc(strlen(dossier) + strlen(commande) + 2);
		if (!complet)
			return (NULL);
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
