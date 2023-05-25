#include "main.h"

/**
 * is_chain - test if current charcter in buffer is a chain delimet
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of curr position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chain(info_t *inf, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|')
	{
		if (buf[j + 1] == '|')
		{
			buf[j] = 0;
			j++;
			inf->cmd_buf_type = CMD_OR;
		}
		else
		{
			open_pipefd(inf);
			buf[j] = 0;
			inf->cmd_buf_type = CMD_PIPE;
		}
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this cmd */
	{
		buf[j] = 0; /* replace semicolon with 0 */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - The checks should continue chaining based on last stats
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of current position in buffer
 * @i: starting position in buffer
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *inf, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	else if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	else if (inf->cmd_buf_type == CMD_PIPE)
	{
		/*printf(YEL "CHECK_PIPE" RESL);*/
		inf->left_redirect_from_fd = inf->pipefd[0];
		inf->pipefd[0] = 0;
		inf->pipefd[1] = 0;
	}

	*p = j;
}

/**
 * replace_alias - It replaces an aliases in the tokenized str
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int repl_alias(info_t *inf)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - It replaces vars in the tokenized str
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int repl_var(info_t *inf)
{
	int i = 0;
	list_t *node;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!_strcmp(inf->argv[i], "$?"))
		{
			repl_var(&(inf->argv[i]),
				_strdup(convert_num(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[i], "$$"))
		{
			repl_var(&(inf->argv[i]),
				_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = starts_with(inf->env, &inf->argv[i][1], '=');
		if (node)
		{
			repl_var(&(inf->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		repl_var(&inf->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces str
 * @old: address of old str
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int repl_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
