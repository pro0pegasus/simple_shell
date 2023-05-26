#include "lists.h"

/**
 * free_listtoken - it frees listtoken_t lst
 *
 * Description: it frees listtoken_t lst
 *
 * @head: points to a pointer that points to the first node
 *
 * Return: void
 */
void free_listtoken(listtoken_t **head)
{
	listtoken_t *node;

	if (head == NULL)
		return;

	while (*head != NULL)
	{
		node = *head;
		*head = node->next;
		free(node->token);
		free(node);
	}
	head = NULL;
}
