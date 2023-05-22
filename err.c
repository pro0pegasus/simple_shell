#include "main.h"

/**
 * print_error -It prints an err msg
 * @info: parameter and return info struct
 * @estr: string contains specified err type
 * Return: 0 if no num in string, converted num otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_error_noarg -It prints an err msg w/o arg
 * @info: parameter and return info struct
 * @estr: string contains specified err type
 * Return: 0 if no num in string, converted num otherwise
 *        -1 on error
 */
void print_error_noarg(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(estr);
	_eputchar(BUF_FLUSH);
}
