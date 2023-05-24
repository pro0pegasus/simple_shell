#include "main.h"

/**
 * interactive - if shell is interactive return true
 * @inf: adress of struct
 *
 * Return: 0 if no interactive mode and 1 otherwise
 */
int interactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_deli - see if char is delimeter
 * @ch: checked character
 * @deli: delim str
 * Return: 0 if false otherwise 1
 */
int is_deli(char ch, char *deli)
{
	while (*deli)
		if (*deli++ == ch)
			return (1);
	return (0);
}

/**
 * _isal - alphabetic char checker
 * @ch: inputed character
 * Return: 0 if ch is not alphabetic, 1 otherwise
 */
int _isal(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - turns string to integ
 * @st: converted stri
 * Return: converted number if number in string, 0 otherwise
 */
int _atoi(char *st)
{
	int j, sig = 1, fl = 0, output;
	unsigned int res = 0;

	for (j = 0; st[j] != '\0' && fl != 2; j++)
	{
		if (st[j] == '-')
			sig *= -1;
		if (st[j] >= '0' && st[j] <= '9')
		{
			fl = 1;
			res *= 10;
			res += (s[j] - '0');
		}
		else if (fl == 1)
			fl = 2;
	}
	if (sig == -1)
		output = -res;
	else
		output = res;

	return (output);
}
