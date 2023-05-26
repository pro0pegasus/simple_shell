#include "lists.h"
#include <stdio.h>

/**
 * print_listtoken - prints all listtoken_t lst elements
 * @head: points the first node
 *
 * Return: num of nodes
 */
size_t print_listtoken(const listtoken_t *head)
{
	int count = 0;
	const listtoken_t *current;

	if (head == NULL)
		return (0);

	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->token);
		count++;

		current = current->next;
	}

	return (count);
}
