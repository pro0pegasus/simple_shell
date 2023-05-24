#include "main.h"

/**
 * input_buff - buff commands
 * @inf: struct parameter
 * @buff: buffer adress
 * @leng: len var adress
 * Return: bytes read
 */
ssize_t input_buff(info_t *inf, char **buff, size_t *leng)
{
	ssize_t r = 0;
	size_t leng_p = 0;

	if (!*leng)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, siginthandle);
#if USE_GETLINE
		r = getline(buff, &leng_p, stdin);
#else
		r = _getline(inf, buff, &leng_p);
		if (r == -1 && inf->startup_fd > -1)
		{
			close(inf->startup_fd);
			inf->startup_fd = -1;
			r = _getline(inf, buff, &leng_p);
		}
#endif
		if (r >= 0)
		{
			if (inf->hdoc)
				return (parse_hdoc(inf, buff, r));
			if (r > 0 && (*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			inf->linecountF = 1;
			rmv_comment(*buff);
			build_hist_lst(inf, *buff, inf->Hcount++);
			/* if (_strchr(*buff, ';'))*/
			{
				*leng = r;
				inf->cmd_buf = buff;
			}
		}
	}
	return (r);
}

/**
 * get_inp - get line withour newline
 * @inf: struct parameter
 * Return: bytes read
 */
ssize_t get_inp(info_t *inf)
{
	static char *buff;
	static size_t j, k, leng;
	ssize_t r = 0;
	char **buf_pe = &(inf->arg), *pe;

	_putchar(BUF_FLUSH);
	r = input_buff(inf, &buff, &leng);
	if (r == -1)
		return (-1);
	if (leng)
	{
		k = j;
		pe = buff + j;

		chain_check(inf, buff, &k, j, leng);
		while (k < leng)
		{
			if (chain(inf, buff, &k))
				break;
			k++;
		}

		j = k + 1;
		if (j >= leng)
		{
			j = leng = 0;
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_pe = pe;
		return (_strlen(pe));
	}

	*buf_pe = buff;
	return (r);
}

/**
 * read_buff - buffer reader
 * @inf: struct parameter
 * @buff: buffer
 * @s: size
 * Return: r
 */
ssize_t read_buff(info_t *inf, char *buff, size_t *s)
{
	ssize_t r = 0;

	if (*s)
		return (0);
	r = read(inf->readfileD, buff, READ_BUF_SIZE);
	if (r >= 0)
		*s = r;
	return (r);
}

/**
 * _getline - gets from STDIN the next line in input
 * @inf: struct parameter
 * @pter: pointer to buffer adress, NULL or preallocated
 * @leng: NULL or size of preallocated pointer buffer
 * Return: s
 */
int _getline(info_t *inf, char **pter, size_t *leng)
{
	size_t r;

	(void) leng;
	*pter = _getline(inf->startup_fd > -1 ? inf->startup_fd : inf->readfileD);
	if (!*pter)
		r = -1;
	else
		r = _strlen(*pter);
	return (r);
}

/**
 * siginthandle - ctrl-C blocker
 * @sig_numb: signal number
 * Return: void
 */
void siginthandle(__attribute__((unused))int sig_numb)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
