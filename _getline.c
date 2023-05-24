#include "get.h"

/**
 * __get - getting lines of characters from a file descrip
 * @fileD: the descriptor file
 * Return: line pointer
 */

char *__get(const int fileD)
{
	static fileDBuff hd;
	fileDBuff *fileB = NULL, *temp;
	char *line = NULL;

	if (fileD == -1)
	{
		if (hd.buff)
			hd.buff = (free(hd.buff), NULL);
		for (fileB = hd.nxt; fileB;)
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
		_memset((void *)*hd, 0, sizeof(hd));
		return (NULL);
	}
	fileB = get_fileDBuff(&hd, fileD);
	if (fileB)
		line = __read_buff(fileB);
	if (line && line[0] == '\n' && !line[1])
		line[0] = 0;
	return (line);
}
/**
 * __read_buff - reads buffer
 * @fileB: the file buff struct
 * Return: -1 on error and 0 on success
 */
char *__read_buff(fileDBuff *fileB)
{
	char buff[READ_SIZE + 1], *pe, *line;
	ssize_t r = 0;

	pe = _strchr(fileB->buff + fileB->j, '\n', fileB->leng - fileB->j);
	if (!fileB->leng || fileB->j >= fileB->leng || !pe)
	{
		while (1)
		{
			r = read(fileB->fileD, buff, READ_SIZE);
			if (r < 0 || (r == 0 && !fileB->leng))
				return (fileB->buff ? (free(fileB->buff), NULL) : NULL);
			if (r == 0)
			{
				pe = fileB->buff + fileB->leng;
				break;
			}
			fileB->buff = _realloc(fileB->buff, fileB->leng, fileB->leng + r + 1);
			if (!fileB->buff)
				return (NULL);
			_memcpy((void *)(fileB->buff + fileB->leng), buff, r), fileB->leng += r;
			pe = _strchr(fileB->buff + (fileB->leng - r), '\n', r);
			if (pe)
			{
				fileB->buff[fileB->leng] = 0;
				break;
			}
		}
	}
	*pe = '\0';
	line = malloc(1 + (pe - (fileB->buff + fileB->j)));
	if (!line)
		return (NULL);
	_memcpy((void *)line, fileB->buff + fileB->j, 1 + (pe - (fileB->buff + fileB->j)));
	fileB->j = (pe - fileB->buff) + 1;
	if (fileB->j >= fileB->leng)
	{
		fileB->j = fileB->leng = 0;
		fileB->buff = (free(fileB->buff), NULL);
	}
	return (line);
}
/**
 * get_fileDBuff - adds to linked lists
 * @hd: head node from pointer
 * @fileD: file descrip from buf to get
 * Return: the pointer towards the fileD buff node
 */
fileDBuff *get_fileDBuff(fileDBuff *hd, const int fileD)
{
	fileDBuff *node;

	if (!hd->buff && !hd->fileD && !hd->nxt)
	{
		hd->fileD = fileD;
		return (hd);
	}
	for (; hd->nxt && hd->nxt->fileD <= fileD; hd = hd->nxt)
		;
	if (hd->fileD == fileD)
		return (hd);
	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	if (fileD < hd->fileD)
	{
		_memcpy((void *)node, (void *)hd, sizeof(*hd));
		_memset((void *)hd, 0, sizeof(*hd));
		hd->fileD = fileD;
		hd->nxt = node;
		return (hd);
	}
	_memset((void *)node, 0, sizeof(*node));
	node->fileD = fileD;
	node->nxt = hd->nxt;
	hd->nxt = node;
	return (node);
}
/**
 **__strchr - finds location of a charac in a string
 *@t: parsed string
 *@b: the character to find
 *@s: number of bytes to find
 *Return: (t) the memory area t pointer
 */
char *__strchr(char *t, char b, ssize_t s)
{
	if (!t)
		return (NULL);
	do {
		if (*t == b)
			return (t);
		t++;
	} while (--s > 0);
	return (NULL);
}
