#include "main.h"

/**
 * sigint_handler - handles sigs
 * @signal: sig
 *
 * Return: nothing
 */
void sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		prompt();
		fflush(stdout);
	}
}
