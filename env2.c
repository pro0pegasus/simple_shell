#include "main.h"

/**
 * get_environ - It returns the str array copy of the env
 * @inf: The structure contains potential args. It is Used to maintain
 *          constant func prototype.
 * Return: Always 0
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Remove the env var
 * @inf: The structure contains potential args. It is Used to maintain
 *        constant func prototype.
 *  Return: 1 delete, 0 otherwise
 * @var: the str env var property
 */
int _unsetenv(info_t *inf, char *var)
{
	list_t *node = inf->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->nxt;
		i++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - It Initializes a new env var,
 *             or modify an existing one
 * @inf: The structure contains potential args. It is used to maintain
 *        constant func prototype.
 * @var: str env var property
 * @value: string env var value
 *  Return: Always 0
 */
int _setenv(info_t *inf, char *var, char *value)
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
	node = inf->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			inf->env_changed = 1;
			return (0);
		}
		node = node->nxt;
	}
	add_node_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}

/**
 * print_prompt - It prints PS1 if exists
 * @inf: info structure
 * Return: void
 */
void print_prompt(info_t *inf)
{
	char hostname[WRITE_BUF_SIZE + 1];
	char *_PS1 = NULL, *prompt = NULL;

	prompt = _getenv(inf, "PS1=");
	if (!prompt)
		_puts("$ ");
	else
	{
		if (_strcmp(prompt, "\\!") == 0)
			_PS1 = convert_num(inf->histcount, 10, 0);
		else if (_strcmp(prompt, "\\a") == 0)
			_PS1 = "\a";
		else if (_strcmp(prompt, "\\d") == 0)
			_PS1 = make_date();
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
			_PS1 = _getenv(inf, "USER=");
		else if (_strcmp(prompt, "\\w") == 0)
			_PS1 = _getenv(inf, "PWD=");
		else
			_puts(prompt);
		_puts(_PS1);
	}
}
