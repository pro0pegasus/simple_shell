#include "main.h"

/**
 * get_historyf - It gets the hist file
 * @inf: parameter structure
 *
 * Return: allocated str containg hist file
 */
char *get_historyf(info_t *inf)
{
	char *buf, *dir;

	dir = _getenv(inf, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist - It creates a file, or appends to an existing file
 * @inf: the parameter structure
 *
 * Return: 1 on success, else -1
 */
int write_hist(info_t *inf)
{
	ssize_t fd;
	char *filename = get_historyf(inf);
	list_t *node = NULL;

	/* printf("WRITE HISTORY(): [%s]\n", filename); */
	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = inf->history; node; node = node->nxt)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - It reads hist from file
 * @inf: parameter structure
 *
 * Return: histcount on success, 0 otherwise
 */
int read_hist(info_t *inf)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_historyf(inf);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hist_lst(inf, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_hist_lst(inf, buf + last, linecount++);
	free(buf);
	inf->Hcount = linecount;
	while (inf->Hcount-- >= INT_MAX)
		del_node_ind(&(inf->history), 0);
	read_hist(inf);
	return (inf->Hcount);
}

/**
 * build_hist_lst - It adds entry to a hist linked list
 * @inf: The structure contains potential args. It is used to maintain
 * @buf: buffer
 * @linecount: history linecount, histcount
 *
 * Return: Always 0
 */
int build_hist_lst(info_t *inf, char *buf, int linecount)
{
	list_t *node = NULL;

	if (inf->history)
		node = inf->history;
	add_node_end(&node, buf, linecount);

	if (!inf->history)
		inf->history = node;
	return (0);
}

/**
 * renum_hist - It renumbers the hist linked list after changes
 * @inf: The structure contains potential args. It is used to maintain
 *
 * Return: new histcount
 */
int renum_hist(info_t *inf)
{
	list_t *node = inf->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->nxt;
	}
	return (inf->Hcount = i);
}
