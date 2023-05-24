#include "main.h"

/**
 * is_chain - test if current charcter in buffer is a chain delimet
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of curr position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|')
	{
		if (buf[j + 1] == '|')
		{
			buf[j] = 0;
			j++;
			info->cmd_buf_type = CMD_OR;
		}
		else
		{
			open_pipefd(info);
			buf[j] = 0;
			info->cmd_buf_type = CMD_PIPE;
		}
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this cmd */
	{
		buf[j] = 0; /* replace semicolon with 0 */
		info->cmd_buf_type = CMD_CHAIN;
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
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	else if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	else if (info->cmd_buf_type == CMD_PIPE)
	{
		/*printf(YEL "CHECK_PIPE" RESL);*/
		info->left_redirect_from_fd = info->pipefd[0];
		info->pipefd[0] = 0;
		info->pipefd[1] = 0;
	}

	*p = j;
}

/**
 * replace_alias - It replaces an aliases in the tokenized str
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - It replaces vars in the tokenized str
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_vars(&(info->argv[i]),
				_strdup(convert_num(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_vars(&(info->argv[i]),
				_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_vars(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_vars(&info->argv[i], _strdup(""));

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
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
