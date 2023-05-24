#include "main.h"

/**
 * _errato - turns string to integ
 * @st: converted string
 * Return: converted number if number in string, 0 otherwise, -1 err
 */
int _errato(char *st)
{
	int j = 0;
	unsigned long int res = 0;

	if (*st == '+')
		st++;
	for (j = 0; st[j] != '\0'; j++)
	{
		if (st[j] >= '0' && st[j] <= '9')
		{
			res *= 10;
			res += (st[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_d - print decimal number
 * @inp: input
 * @filed: decriptor file
 * Return: the amount of charac typed
 */
int print_d(int inp, int filed)
{
	int (*__putchar)(char) = _putchar;
	int j, coun = 0;
	unsigned int _abs_, curr;

	if (filed == STDERR_FILENO)
		__putchar = _eputchar;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		coun++;
	}
	else
		_abs_ = inp;
	curr = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs / j)
		{
			__putchar('0' + curr / j);
			coun++;
		}
		curr %= j;
	}
	__putchar('0' + curr);
	coun++;

	return (coun);
}

/**
 * convert_num - clone of itoa a functions that converts
 * @numb: num
 * @bass: the base
 * @fl: flags of argument
 * Return: a string
 */
char *convert_num(long int numb, int bass, int fl)
{
	static char *arr;
	static char buff[50];
	char sig = 0;
	char *pontr;
	unsigned long n = numb;

	if (!(fl & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sig = '-';
	}
	arr = fl & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	potr = &buff[49];
	*potr = '\0';

	do {
		*--potr = arr[n % bass];
		n /= bass;
	} while (n != 0);

	if (sign)
		*--potr = sig;
	return (potr);
}

/**
 * rmv_comment - removes comments
 * @buff: the string to modify's adress
 * Return: 0;
 */
void rmv_comment(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}

