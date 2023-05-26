#include "main.h"

/**
 * digit_counter - it counts digit
 * @command_num: num to be counted
 *
 * Return: num of the digits
 */
int digit_counter(size_t command_num)
{
	int digit_count = 0;

	if (command_num == 0)
		return (1);
	while (command_num != 0)
	{
		command_num /= 10;
		digit_count++;
	}

	return (digit_count);
}
