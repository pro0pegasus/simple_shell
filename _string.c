#include "main.h"

/**
 * rev_string - revs a str
 * @str: str
 *
 * Return: void
 */
void rev_string(char *str)
{
	int i, len;
	char tmp;

	len = 0;
	while (str[len] != '\0')
		len++;
	len--;
	for (i = 0; i < len; i++, len--)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
	}
}

/**
 * _itoa - it converts int to a str
 * @command_num: num to convert
 *
 * Return: converted int
 */
char *_itoa(size_t command_num)
{
	char *str = malloc(sizeof(char) * (32 + 1));
	int i = 0;

	do {
		str[i++] = command_num % 10 + '0';
		command_num /= 10;
	} while (command_num > 0);
	str[i] = '\0';
	rev_string(str);

	return (str);
}
