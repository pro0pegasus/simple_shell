#include "main.h"

/**
 * free_main - the array is freed of tokens in the main func
 * @array_of_tokens: tokenized str
 * @input: str
 *
 * Return: void
 */
void free_main(char **array_of_tokens, char *input)
{
	int index;

	for (index = 0; array_of_tokens[index]; index++)
		free(array_of_tokens[index]);
	free(array_of_tokens);
	free(input);
}

/**
 * free_which - short descrip
 *
 * Description: long descrip
 *
 * @path_var: arg_1 descrip
 * @array_of_tokens: arg_2 descrip
 *
 * Return: return descrip
 */
void free_which(char **path_var, char **array_of_tokens)
{
	int index;

	if (array_of_tokens != NULL)
	{
		for (index = 0; array_of_tokens[index]; index++)
			if (array_of_tokens[index] != NULL)
				free(array_of_tokens[index]);
		free(array_of_tokens);
	}
	if (*path_var != NULL)
		free(*path_var);
}
