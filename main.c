#include "main.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 1 on error, 0 on success
 */
int main(int ac, char **av)
{
	info_t inf[] = { INFO_INIT };

	if (ac == 2)
	{
		inf->readfd = open_fle(inf, av[1], 0);
		if (inf->readfd == -1)
		{
			free_info(inf, 1);
			exit(inf->err_num);
		}
	}
	pop_env_lst(inf);
	read_hist(inf);
	read_startup_fd(inf);
	shell(inf, av);
	return (EXIT_SUCCESS);
}
