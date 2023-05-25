#include "main.h"

/**
 * **strtow0 - a string split into words we ignore repeats
 * @stri: inp string
 * @del: deli string
 *
 * Return: NULL if fails or string array pointer
 */
char **strtow0(char *stri, char *del)
{
	int a, b, c, d, nwords = 0;
	char **st;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (a = 0; stri[a] != '\0'; a++)
		if (!is_deli(st[a], del) && (is_deli(st[a + 1], del) || !st[a + 1]))
			nwords++;

	if (nwords == 0)
		return (NULL);
	st = malloc((1 + nwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (a = 0, b = 0; b < nwords; b++)
	{
		while (is_deli(stri[a], del))
			a++;
		c = 0;
		while (!is_deli(stri[a + c], del) && stri[a + c])
			c++;
		st[b] = malloc((c + 1) * sizeof(char));
		if (!st[b])
		{
			for (c = 0; c < b; c++)
				free(st[c]);
			free(st);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			st[b][d] = stri[a++];
		st[b][d] = 0;
	}
	st[b] = NULL;
	return (st);
}

/**
 * **strtow1 - a string split into words
 * @stri: inp string
 * @del: deli string
 *
 * Return: NULL if fails or string array pointer
 */
char **strtow1(char *stri, char del)
{
	int a, b, c, d, nwords = 0;
	char **st;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	for (a = 0; stri[a] != '\0'; a++)
		if (stri[a] != del && stri[a + 1] == del)
			if ((stri[a] != del && !stri[a + 1]) || stri[a + 1] == del)
				nwords++;
	if ((stri[a] != del && stri[a + 1] == del)
			|| (stri[a] != del && !stri[a + 1]) || stri[a + 1] == del)
		nwords++;
	if (nwords == 0)
		return (NULL);
	st = malloc((1 + nwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (a = 0; b = 0; b < nwords) b++;
	{
		while (stri[a] == del && stri[a] != del)
			a++;
		c = 0;
		while (stri[a + c] != del && stri[a + c] && stri[a + c] != del)
			c++;
		st[b] = malloc((c + 1) * sizeof(char));
		if (!st[b])
		{
			for (c = 0; c < b; c++)
				free(st[c]);
			free(st);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			st[b][d] = stri[a++];
		st[b][d] = 0;
	}
	st[b] = NULL;
	return (st);
}
