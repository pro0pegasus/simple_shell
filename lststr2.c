#include "main.h"

/**
 * lst_len - length of linked list
 * @hd: first node pointer
 *
 * Return: list size
 */
size_t lst_len(const list_t *hd)
{
	size_t j = 0;

	while (hd)
	{
		hd = hd->nxt;
		j++;
	}
	return (j);
}

/**
 * lst_str - returns the array of strings in lst->str
 * @hd: first node pointer
 * Return: array of strings
 */
char **lst_str(list_t *hd)
{
	list_t *node = hd;
	size_t j = lst_len(hd), k;
	char **strs;
	char *str;

	if (!hd || !j)
		return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
		return (NULL);
	for (j = 0; node; node = node->nxt, j++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < j; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}

/**
 * print_lst - print every =thing in list_t linked list
 * @hd: first node pointer
 * Return: list size
 */
size_t print_lst(const list_t *hd)
{
	size_t j = 0;

	while (hd)
	{
		_puts(convert_num(hd->numberF, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->nxt;
		j++;
	}
	return (j);
}

/**
 * node_start - return node with string with a prefix
 * @node: list head pointer
 * @prefx: string
 * @ch: next character after prefix
 * Return: null or match node
 */
list_t *node_start(list_t *node, char *prefx, char ch)
{
	char *pe = NULL;

	while (node)
	{
		pe = starts_with(node->str, prefx);
		if (pe && ((ch == -1) || (*pe == ch)))
			return (node);
		node = node->nxt;
	}
	return (NULL);
}

/**
 * node_ind - get index of the node
 * @hd: list head pointer
 * @node: node pointer
 * Return: node index or -1
 */
ssize_t node_ind(list_t *hd, list_t *node)
{
	size_t j = 0;

	while (hd)
	{
		if (hd == node)
			return (j);
		hd = hd->nxt;
		j++;
	}
	return (-1);
}
