#include "get.h"

/**
 * __get - getting lines of characters from a file descrip
 * @fileD: the descriptor file
 * Return: line pointer
 */

char *__get(const int fileD)
{
	static fileDBuff head;
	fileDBuff *fileB = NULL, *temp;
	char *line = NULL;

	if (fileD == -1)
	{
		if (head.buff)
			head.buff = (free(head.buff), NULL);
		for (fileB = head.nxt; fileB;)
		{
			if (fileB->buff)
			{
				free(fileB->buff);
				fileB->buff = NULL;
			}
			temp = fileB;
			fileB = fileB->nxt;
			free(temp);
		}
		_memset((void *)&head, 0, sizeof(head));
		return (NULL);
	}
	fileB = get_fileDBuff(&head, fileD);
	if (fileB)
		line = __read_buff(fileB);
	if (line && line[0] == '\n' && !line[1])
		line[0] = 0;
	return (line);
}
/**
 * __read_buff - reads buffer
 * @fB: the file buff struct
 * Return: -1 on error and 0 on success
 */
char *__read_buff(fileDBuff *fB)
{
	char buff[READ_SIZE + 1], *pe, *line;
	ssize_t r = 0;

	pe = __strchr(fB->buff + fB->j, '\n', fB->leng - fB->j);
	if (!fB->leng || fB->j >= fB->leng || !pe)
	{
		while (1)
		{
			r = read(fB->fileD, buff, READ_SIZE);
			if (r < 0 || (r == 0 && !fB->leng))
				return (fB->buff ? (free(fB->buff), NULL) : NULL);
			if (r == 0)
			{
				pe = fB->buff + fB->leng;
				break;
			}
			fB->buff = _realloc(fB->buff, fB->leng, fB->leng + r + 1);
			if (!fB->buff)
				return (NULL);
			_memcpy((void *)(fB->buff + fB->leng), buff, r), fB->leng += r;
			pe = __strchr(fB->buff + (fB->leng - r), '\n', r);
			if (pe)
			{
				fB->buff[fB->leng] = 0;
				break;
			}
		}
	}
	*pe = '\0';
	line = malloc(1 + (pe - (fB->buff + fB->j)));
	if (!line)
		return (NULL);
	_memcpy((void *)line, fB->buff + fB->j, 1 + (pe - (fB->buff + fB->j)));
	fB->j = (pe - fB->buff) + 1;
	if (fB->j >= fB->leng)
	{
		fB->j = fB->leng = 0;
		fB->buff = (free(fB->buff), NULL);
	}
	return (line);
}
/**
 * get_fileDBuff - adds to linked lists
 * @head: head node from pointer
 * @fileD: file descrip from buf to get
 * Return: the pointer towards the fileD buff node
 */
fileDBuff *get_fileDBuff(fileDBuff *head, const int fileD)
{
	fileDBuff *node;

	if (!head->buff && !head->fileD && !head->nxt)
	{
		head->fileD = fileD;
		return (head);
	}
	for (; head->nxt && head->nxt->fileD <= fileD; head = head->nxt)
		;
	if (head->fileD == fileD)
		return (head);
	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	if (fileD < head->fileD)
	{
		_memcpy((void *)node, (void *)head, sizeof(*head));
		_memset((void *)head, 0, sizeof(*head));
		head->fileD = fileD;
		head->nxt = node;
		return (head);
	}
	_memset((void *)node, 0, sizeof(*node));
	node->fileD = fileD;
	node->nxt = head->nxt;
	head->nxt = node;
	return (node);
}
/**
 **__strchr - finds location of a charac in a string
 *@t: parsed string
 *@b: the character to find
 *@s: number of bytes to find
 *Return: (t) the memory area t pointer
 */
char *__strchr(char *st, char b, ssize_t s)
{
	if (!st)
		return (NULL);
	do {
		if (*st == b)
			return (st);
		st++;
	} while (--s > 0);
	return (NULL);
}
