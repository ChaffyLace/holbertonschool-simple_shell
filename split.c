#include "shell.h"

char **split_line(char *line)
{
	int i = 0;
	char *token;
	char **tokens = malloc(sizeof(char *) * 64);

	if (!tokens)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token)
	{
		tokens[i] = strdup(token);
		i++;
		token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

void free_array(char **arr)
{
	int i = 0;

	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
