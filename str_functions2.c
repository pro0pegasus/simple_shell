#include "main.h"

/**
 * _strcpy - copy string
 * @dest: destination
 * @src: source
 * Return: destination pointer
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - duplicating string
 * @str: duplicate this string
 * Return: duplicated string pointer
 */
char *_strdup(const char *str)
{
	int leng = 0;
	char *re;

	if (str == NULL)
		return (NULL);
	while (*str++)
		leng++;
	re = malloc(sizeof(char) * (leng + 1));
	if (!re)
		return (NULL);
	for (len++; leng--;)
		re[leng] = *--str;
	return (re);
}

/**
 * _puts - it print a input string
 * @str: printed string
 * Return: doesnt return anything
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - write character ch to stdout
 * @ch: printed character
 * Return: 1 if successful
 * On error, returns -1, and it sets errno
 */
int _putchar(char ch)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		buff[j++] = ch;
	return (1);
}
