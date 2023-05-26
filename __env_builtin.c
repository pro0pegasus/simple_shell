#include "main.h"

/**
 * _env_builtin - print env
 *
 * @array_of_tokens: cmd array
 *
 * Return: 0  failure 1  Sucess
 */
int _env_builtin(__attribute((unused)) char **array_of_tokens)
{
	int enviroment_index;

	for (enviroment_index = 0; __environ[enviroment_index]; enviroment_index++)
	{
		write(STDOUT_FILENO, __environ[enviroment_index],
				strlen(__environ[enviroment_index]));
		write(STDOUT_FILENO, "\n", strlen("\n"));
	}
	return (enviroment_index);
}
