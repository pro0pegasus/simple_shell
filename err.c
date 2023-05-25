#include "main.h"

/**
 * print_err - It prints an err msg
 * @inf: parameter and return info struct
 * @str: string contains specified err type
 * Return: 0 if no num in string, converted num otherwise
 *        -1 on error
 */
void print_err(info_t *inf, char *str)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(str);
}

/**
 * print_err_noarg - It prints an err msg w/o arg
 * @inf: parameter and return info struct
 * @str: string contains specified err type
 * Return: 0 if no num in string, converted num otherwise
 *        -1 on error
 */
void print_err_noarg(info_t *inf, char *str)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(str);
	_eputchar(BUF_FLUSH);
}
