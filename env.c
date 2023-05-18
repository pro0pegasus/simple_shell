#include "main.h"


/**
 * _myenv - it prints the current environment
 * @info: The structure contains potential arguments. It is used to maintain
 *          constant function prototype.
 * Return: Always - 0
 */
int _myenv(info_t *info)
{
        print_lst_string(info->env);
        return (0);
}

/**
 * _getenv - it  gets the value of an env var
 * @info: The structure contains potential arguments. It is used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
        list_t *node = info->env;
        char *p;

        while (node)
        {
                p = starts_with(node->str, name);
                if (p && *p)
                        return (p);
                node = node->nxt;
        }
        return (NULL);
}

/**
 * _mysetenv - It initialize a new env var,
 *             or modify an existing
 * @info: The structure contains potential arguments. It is Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
        if (info->argc != 3)
        {
                _eputs("Incorrect number of arguements\n");
                return (1);
        }
        if (_setenv(info, info->argv[1], info->argv[2]))
                return (0);
        return (1);
}

/**
 * _myunsetenv - It remove an env var
 * @info: The structure contains potential arguments. It is used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
        int i;

        if (info->argc == 1)
        {
                _eputs("Too few arguements.\n");
                return (1);
        }
        for (i = 1; i <= info->argc; i++)
                _unsetenv(info, info->argv[i]);

        return (0);
}

/**
 * populate_env_list - It populates env linked list
 * @info: The structure contains potential arguments. It is used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
        list_t *node = NULL;
        size_t i;

        for (i = 0; environ[i]; i++)
                add_node_end(&node, environ[i], 0);
        info->env = node;
        return (0);
}