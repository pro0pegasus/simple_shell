#include "main.h"

/**
 * print_error -It prints an err msg
 * @info: parameter and return info struct
 * @estr: string contains specified err type
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
 * print_error_noarg -It prints an err msg w/o arg
 * @info: parameter and return info struct
 * @estr: string contains specified err type
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
