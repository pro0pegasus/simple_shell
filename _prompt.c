#include "main.h"

/**
 * prompt - a short descrip
 *
 * Description: a long descrip
 *
 * Return: -1 on failure, 0 on success
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", strlen("$ "));
}
