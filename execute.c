#include "shell.h"

/**
 * _getenv - find env variable
 * @nom: name
 * Return: value
 */
char *_getenv(char *nom)
{
	int i = 0;
	size_t len = strlen(nom);

	while (environ && environ[i])
	{
		if (strncmp(environ[i], nom, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * chercher_chemin - find command in PATH
 * @commande: cmd name
 * Return: full path
 */
char *chercher_chemin(char *commande)
{
	char *path, *copie, *token, *complet;
	struct stat st;

	path = _getenv("PATH");
	if (!path || strlen(path) == 0)
		return (NULL);
	copie = strdup(path);
	token = strtok(copie, ":");
	while (token)
	{
		complet = malloc(strlen(token) + strlen(commande) + 2);
		strcpy(complet, token);
		strcat(complet, "/");
		strcat(complet, commande);
		if (stat(complet, &st) == 0)
		{
			free(copie);
			return (complet);
		}
		free(complet);
		token = strtok(NULL, ":");
	}
	free(copie);
	return (NULL);
}
