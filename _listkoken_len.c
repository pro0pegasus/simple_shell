#include "lists.h"

/**
 * listtoken_len - returns num of elements
 * @head: it points to the first node
 *
 * Return: the num of elements in linked listtoken_t lst
 */
size_t listtoken_len(const listtoken_t *head)
{
	int count = 0;
	const listtoken_t *current;

	if (head == NULL)
		return (0);

	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	return (count);
}
