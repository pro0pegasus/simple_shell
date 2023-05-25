#include "main.h"

/**
 * _myhist - It displays history list, one cmd by line, preceded
 *              with line nums, starting at 0.
 * @inf: The structure contains potential args. Used to maintain
 *        constant func prototype.
 *  Return: Always 0
 */

int _myhist(info_t *inf)
{
	print_lst(inf->history);
	return (0);
}

/**
 * unset_alias - It sets alias to str
 * @inf: the parameter structure
 * @str: the str alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *inf, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(inf->alias),
		del_node_ind(inf->alias, starts_with(inf->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - It sets alias to str
 * @inf: The parameter structure
 * @str: the strg alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *inf, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(inf, str));

	unset_alias(inf, str);
	return (add_node_end(&(inf->alias), str, 0) == NULL);
}

/**
 * print_alias - It prints an alias str
 * @node: alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - It mimics the alias builtin
 * @info: The structure contains potential args. Used to maintain
 *          constant funct prototype.
 *  Return: Always 0
 */
int _myalias(info_t *inf)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->nxt;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		p = _strchr(inf->argv[i], '=');
		if (p)
			set_alias(inf, inf->argv[i]);
		else
			print_alias(starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
