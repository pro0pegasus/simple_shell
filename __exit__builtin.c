#include "main.h"

/**
 * _exit_builtin - exit builtin
 *
 * @array_of_tokens: cmd array
 *
 * Return: 0 failure 1 sucess
 */
int _exit_builtin(char **array_of_tokens)
{
	if (array_of_tokens[1] != NULL)
		exit(atoi(array_of_tokens[1]));
	else
		return (EXIT_CODE);
}
