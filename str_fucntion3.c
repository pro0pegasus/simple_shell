#include "main.h"

/**
 * *_strncpy - it copy strings
 * @dest: string of the destination
 * @src: string of the source
 * @num: number of charcters to copy
 * Return: concat string
 */
char *_strncpy(char *dest, char *src, int num)
{
	int j, k;
	char *st = dest;

	j = 0;
	while (src[j] != '\0' && j < num - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < num)
	{
		k = j;
		while (k < num)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (st);
}

/**
 * *_strncat - two strings concatenation
 * @dest: string one
 * @src: string two
 * @num: max bytes used
 * Return: concat string
*/
char *_strncat(char *dest, char *src, int num)
{
	int j, k = 0;
	char *st = dest;

	while (dest[j] != '\0')
		j++;
	while (src[k] != '\0' && k < num)
	{
		dest[j] = src[k];
		j++;
		k++;
	}
	if (k < num)
		dest[j] = '\0';
	return (st);
}

/**
 * *_strchr - character locating in a string
 * @st: parsed string
 * @ch: the looked for character
 * Return: (s) memory area s pointer
 */
char *_strchr(char *st, char ch)
{
	do {
		if (*st == ch)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}

/**
 * * _strchlast - final matching character in string's location
 *  @s: parsed string
 *  @c: looked for charac
 *  Return: matching character's adress
 */
char *_strchlast(char *c, char s)
{
	char *re = NULL, *pe;

	while ((pe = _strchr(c, s)))
	{
		re = pe;
		c = pe + 1;
	}
	return (re);
}
