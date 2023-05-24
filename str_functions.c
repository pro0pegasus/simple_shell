#include "main.h"

/**
 * _strlen - return string length
 * @st: string to check length
 * Return: string length
 */
int _strlen(char *st)
{
	int j = 0;

	if (!st)
		return (0);
	while (*st++)
		j++;
	return (j);
}

/**
 * _strcmp - compares two strangs
 * @st1: first str
 * @st2: second str
 * Return: positive if st1>st2, zero if st1==st2 else st1<st2
 */
int _strcmp(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * starts_with - see if haystck begins with nedle
 * @haystck: string to find
 * @nedle: missing substring to search
 * Return: NULL or adress of next char
 */
char *starts_with(const char *haystck, const char *nedle)
{
	while (*nedle)
		if (*nedle++ != *haystck++)
			return (NULL);
	return ((char *)haystck);
}

/**
 * _strcat - concatenate two strings
 * @dest: buffer of destination
 * @src: buffer of source
 * Return: destination buffer pointer
 */
char *_strcat(char *dest, char *src)
{
	char *re = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (re);
}
