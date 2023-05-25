#include "main.h"

/**
 * open_file -It opens a file descriptor,it exits on failure
 * @info: parameter struct
 * @name: name of file to make it open
 * @silent: if true do not print errs
 * Return: fd of file
 */
int open_file(info_t *inf, char *nom, int silence)
{
	int fd;

	fd = open(nom, O_RDONLY);
	if (fd == -1 && !silence)
	{
		if (errno == EACCES)
			inf->err_num = 126;
		if (errno == ENOENT)
		{
			_eputs("./main");
			_eputs(": 0: Can't open ");
			_eputs(nom);
			_eputchar('\n');
			_eputchar(BUF_FLUSH);
			inf->err_num = 127;
		}
		return (-1);
	}
	return (fd);
}

/**
 * read_startup_file -It reads the startup file
 * @info: parameter struct
 */
void read_startup_fd(info_t *inf)
{
	char *buf;

	if (!_getenv(inf, "HOME="))
		return;
	buf = malloc(_strlen(_getenv(inf, "HOME=")) +
		_strlen(START_FILE) + 2);
	if (!buf)
		return;
	*buf = 0;
	sprintf(buf, "%s/%s", _getenv(inf, "HOME="), START_FILE);
	inf->startup_fd = open_file(inf, buf, 1);
	free(buf);
}
