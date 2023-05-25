#include "main.h"

/**
 * add_node - adding a node at the start of a list
 * @hd: pointer to head node adress
 * @str: node field string
 * @numb: index of node used by history
 * Return: list size
 */
list_t *add_node(list_t **hd, const char *str, int numb)
{
	list_t *new_hd;

	if (!hd)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	_memset((void *)new_hd, 0, sizeof(list_t));
	new_hd->numberF = numb;
	if (str)
	{
		new_hd->str = _strdup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->nxt = *hd;
	*hd = new_hd;
	return (new_hd);
}

/**
 * add_node_end - adding a node at the end of a list
 * @hd: head node pointer's adress
 * @str: node field string
 * @numb: index of node used by history
 * Return: list size
 */
list_t *add_node_end(list_t **hd, const char *str, int numb)
{
	list_t *new_nd, *node;

	if (!hd)
		return (NULL);
	node = *hd;
	new_nd = malloc(sizeof(list_t));
	if (!new_nd)
		return (NULL);
	_memset((void *)new_nd, 0, sizeof(list_t));
	new_nd->numberF = numb;
	if (str)
	{
		new_nd->str = _strdup(str);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->nxt)
			node = node->nxt;
		node->nxt = new_nd;
	}
	else
		*hd = new_nd;
	return (new_nd);
}

/**
 * print_lst_string - print the string of a list_t linked list
 * @hd: first node pointer
 * Return: list size
 */
size_t print_lst_string(const list_t *hd)
{
	size_t j = 0;

	while (hd)
	{
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->nxt;
		j++;
	}
	return (j);
}

/**
 * del_node_ind - deleting node in specific index
 * @hd: first node pointer's adress
 * @ind: node index to delete
 * Return: 0 if fail or 1 in success
 */
int del_node_ind(list_t **hd, unsigned int ind)
{
	list_t *node, *prev_nd;
	unsigned int j = 0;

	if (!hd || !*hd)
		return (0);

	if (!ind)
	{
		node = *hd;
		*hd = (*hd)->nxt;
		free(node->str);
		free(node);
		return (1);
	}
	node = *hd;
	while (node)
	{
		if (j == ind)
		{
			prev_nd->nxt = node->nxt;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		prev_nd = node;
		node = node->nxt;
	}
	return (0);
}

/**
  * free_lst - free every node in a list
  * @hd_ptr: head node pointer's adress
  * Return: void
  */
void free_lst(list_t **hd_ptr)
{
	list_t *node, *next_nd, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	node = hd;
	while (node)
	{
		next_nd = node->nxt;
		free(node->str);
		free(node);
		node = next_nd;
	}
	*hd_ptr = NULL;
}
