#include "main.h"

/**
 * parse_redi_left - It  parses redir directives from input
 * @inf: parameter struct
 * Return: void
 */
void parse_redi_left(info_t *inf)
{
	char *p = _strchlast(inf->arg, '<'), *fle;
	int fd;

	if (!p) /* no redir */
		return;

	fle = p + 1;
	if (p > inf->arg && *(p - 1) == '<')
	{
		inf->left_append = 1;
		p--;
	}
	if (p > inf->arg) /* if not start of str */
	{
		/* check if previous charcter is digit */
		if (*(p - 1) >= '0' && *(p - 1) <= '9')
		{
			p--;
			inf->left_redirect_from_fd = *p - '0';
		}
	}
	fd = open_redir(inf, fle, 1);
	if (fd == -1)
	{
		/* TODO: print msg, set status, etc? */
		return;
	}
	inf->left_redirect_from_fd = fd;
	*p = 0; /* insert null char to cut str b4 > */
}

/**
 * parse_redi_right - It parses redir directives from input
 * @inf: parameter struct
 * Return: void
 */
void parse_redi_right(info_t *inf)
{
	char *p = _strchlast(inf->arg, '>'), *fle;
	int fd;

	if (!p) /* no redire */
		return;

	fle = p + 1;
	if (p > inf->arg && *(p - 1) == '>')
	{
		inf->right_append = 1;
		p--;
	}
	if (p > inf->arg) /* if not start of str */
	{
		/* check if previous charchter is digit */
		if (*(p - 1) >= '0' && *(p - 1) <= '9')
		{
			p--;
			inf->right_redirect_from_fd = *p - '0';
		}
	}
	fd = open_redir(inf, fle, 0);
	if (fd == -1)
	{
		/* TODO: print msg, set status, etc? */
		return;
	}
	inf->right_redirect_to_fd = fd;
	*p = 0; /* insert null charcter to cut str before > */
}

/**
 * open_redi - It opens a fd for redir writing
 * @inf: parameter struct
 * @fle: file name
 * @lft: 1 if left, 0 if right
 * Return: int fd or -1
 */
int open_redi(info_t *inf, char *fle, int lft)
{
	int fd;
	char buf[256], *action;

	while (*fle == ' ' || *fle == '\t')
		fle++;
	if (!*fle)
	{
		print_err_noarg(inf, "Syntax error: newline unexpected\n");
		return (-1);
	}
	if (lft)
	{
		if (inf->left_append)
		{
			inf->hdoc = _strdup(fle);
			if (!inf->hdoc)
				exit(1);
			return (DOC_FD);
		}
		fd = open(fle, O_RDONLY);
	}
	else
		fd = open(fle, O_CREAT | O_WRONLY |
			(inf->right_append ? O_APPEND : O_TRUNC), 0666);
	if (fd == -1)
	{
		buf[0] = 0;
		inf->line_count++;
		inf->err_num = inf->status = 2;
		action = lft ? "open" : "create";
		if (errno == EACCES)
			sprintf(buf, "cannot %s %s: Permission denied\n", action, fle);
		else if (errno == ENOENT)
			sprintf(buf, "cannot %s %s: No such file\n", action, fle);
		print_err_noarg(inf, buf);
	}
	return (fd);
}

/**
 * parse_hdoc - It parses line of HDOC input into buffer
 * @inf: parameter struct
 * @buf: getline buffer
 * @s: number of bytes read into getline buffer
 * Return: length of hdoc_cmd if end of hdoc else r
 */
size_t parse_hdoc(info_t *inf, char **buf, size_t s)
{
	static char *hdoc_buf;
	static size_t hdoc_i, hdoc_len;
	size_t len;

	s++;
	if (!_strcmp(inf->hdoc, *buf))
	{
		free((void **)buf);
		*buf = inf->hdoc_cmd;
		inf->hdoc_cmd = NULL;
		len = _strlen(*buf);
		inf->hdoc_txt = hdoc_buf;
		hdoc_buf = NULL;
		hdoc_i = hdoc_len = 0;
		free((void **)&inf->hdoc);
		return (len);
	}
	while (hdoc_len <= s + hdoc_i)
	{
		hdoc_buf = _realloc(hdoc_buf, hdoc_len,
			hdoc_len ? hdoc_len * 2 : START_ARRAY_SIZE);
		if (!hdoc_buf)
			exit(1);
		hdoc_len <<= 1;
		if (!hdoc_len)
		{
			_memset(hdoc_buf, 0, START_ARRAY_SIZE);
			hdoc_len = START_ARRAY_SIZE;
		}
	}
	_strcat(hdoc_buf, *buf);
	_strcat(hdoc_buf, "\n");
	hdoc_i += s;
	return (s);
}

/**
 * rest_stdfd - It restores stdin/out after redir
 * @inf: parameter struct
 */
void rest_stdfd(info_t *inf)
{
	_putchar(BUF_FLUSH);
	_eputchar(BUF_FLUSH);
	if (inf->dup_stdin)
	{
		dup2(inf->dup_stdin, STDIN_FILENO);
		close(inf->dup_stdin);
		inf->dup_stdin = 0;
	}
	if (inf->dup_stdout)
	{
		dup2(inf->dup_stdout, STDOUT_FILENO);
		close(inf->dup_stdout);
		inf->dup_stdout = 0;
	}
}
