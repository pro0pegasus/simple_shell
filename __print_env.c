#include "main.h"

/**
 * _print_env - a short descrip
 *
 * Description: a long descrip
 *
 * Return: return descrip
 */
int _print_env(void)
{
	unsigned int environ_index;

	for (environ_index = 0; __environ[environ_index]; environ_index++)
		printf("%s\n", __environ[environ_index]);
	return (0);
}
