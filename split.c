#include "shell.h"

/**
 * split_line - splits a line into tokens
 * @line: input line
 *
 * Return: array of tokens
 */
char **split_line(char *line)
{
	char **tokens;
	char *token;
	int i = 0;

	tokens = malloc(sizeof(char *) * 64);
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

/**
 * free_array - frees an array of strings
 * @arr: array to free
 */
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
