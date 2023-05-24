#include "main.h"

/**
 * get_environ - It returns the str array copy of the env
 * @info: The structure contains potential args. It is Used to maintain
 *          constant func prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove the env var
 * @info: The structure contains potential args. It is Used to maintain
 *        constant func prototype.
 *  Return: 1 delete, 0 otherwise
 * @var: the str env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->nxt;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - It Initializes a new env var,
 *             or modify an existing one
 * @info: The structure contains potential args. It is used to maintain
 *        constant func prototype.
 * @var: str env var property
 * @value: string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->nxt;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * print_prompt - It prints PS1 if exists
 * @info: info structure
 * Return: void
 */
void print_prompt(info_t *info)
{
	char hostname[WRITE_BUF_SIZE + 1];
	char *_PS1 = NULL, *prompt = NULL;

	prompt = _getenv(info, "PS1=");
	if (!prompt)
		_puts("$ ");
	else
	{
		if (_strcmp(prompt, "\\!") == 0)
			_PS1 = convert_num(info->histcount, 10, 0);
		else if (_strcmp(prompt, "\\a") == 0)
			_PS1 = "\a";
		else if (_strcmp(prompt, "\\d") == 0)
			_PS1 = create_date();
		else if (_strcmp(prompt, "\\H") == 0)
		{
			if (gethostname(hostname, WRITE_BUF_SIZE) == 0)
				_PS1 = hostname;
			else
				perror("gethostname");
		}
		else if (_strcmp(prompt, "\\n") == 0)
			_PS1 = "\n";
		else if (_strcmp(prompt, "\\s") == 0)
			_PS1 = "-hsh";
		else if (_strcmp(prompt, "\\u") == 0)
			_PS1 = _getenv(info, "USER=");
		else if (_strcmp(prompt, "\\w") == 0)
			_PS1 = _getenv(info, "PWD=");
		else
			_puts(prompt);
		_puts(_PS1);
	}
}
