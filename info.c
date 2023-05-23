#include "main.h"

/**
 * clear_info - It initializes infot struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
	if (info->left_redirect_from_fd != DOC_FD)
	{
		/* TODO where else? - when to RESET? */
		info->left_redirect_from_fd = -1;
	}
	info->left_append = 0;
	info->right_redirect_from_fd = 1;
	info->right_redirect_to_fd = -1;
	info->right_append = 0;
}

/**
 * set_info - It initializes info t struct
 * @info: the struct address
 * @av: argument vector
 * Return: 0 if no error else err code
 */
int set_info(info_t *info, char **av)
{
	int i = 0;

	info->err_num = 0;
	info->fname = av[0];
	if (info->arg)
	{
		parse_left_redirect(info);
		parse_right_redirect(info);
		if (info->left_redirect_from_fd == DOC_FD)
		{
			if (!info->hdoc_cmd)
				info->hdoc_cmd = _strdup(info->arg);
		}
		handle_redirects(info);
		info->argv = strtow1(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		repl_alias(info);
		repl_var(info);
	}
	return (info->err_num);
}

/**
 * free_info - It frees info t structure fields
 * @info: structure address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	rest_stdfd(info);
	free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (info->left_redirect_from_fd > 2)
	{
		close(info->left_redirect_from_fd);
		info->left_redirect_from_fd = -1;
	}
	if (info->right_redirect_to_fd > 2)
	{
		close(info->right_redirect_to_fd);
		info->right_redirect_to_fd = -1;
	}
	if (info->hdoc_txt && info->left_redirect_from_fd != DOC_FD)
		free((void **)&info->hdoc_txt);
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_lst(&(info->env));
		if (info->history)
			free_lst(&(info->history));
		if (info->alias)
			free_lst(&(info->alias));
		free((void **)&info->hdoc);
		free((void **)&info->hdoc_txt);
		free((void **)&info->hdoc_cmd);
		free(info->environ);
			info->environ = NULL;
		free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_getline(-1);
		_putchar(BUF_FLUSH);
	}
}

/**
 * print_info - It prints info t structure
 * @info:the struct address
 */
void print_info(info_t *info)
{
	int i = 0;

	printf("info->arg:[%s]\n", info->arg);
	printf("info->argv:%s\n", info->argv ? "" : "[(null)]");
	for (i = 0; info->argv && info->argv[i]; i++)
		printf("\tinfo->argv[%d]:[%s]\n", i, info->argv[i]);
	printf("info->path:[%s]\n", info->path);
	printf("info->argc:[%d]\n", info->argc);
	printf("info->line_count:[%d]\n", info->line_count);
	printf("info->err_num:[%d]\n", info->err_num);
	printf("info->status:[%d]\n", info->status);
	printf("info->fname:[%s]\n", info->fname);
	printf("info->env:[%p]\n", (void *)info->env);
	printf("info->cmd_buf:[%p]\n", (void *)info->cmd_buf);
	printf("info->*cmd_buf:[%s]\n",
	       info->cmd_buf ? *(info->cmd_buf) : "NONE");

	printf("info->left_redirect_from_fd:[%d]\n", info->left_redirect_from_fd);
	printf("info->right_redirect_from_fd:[%d]\n", info->right_redirect_from_fd);
	printf("info->right_redirect_to_fd:[%d]\n", info->right_redirect_to_fd);
	printf("info->left_append:[%d]\n", info->left_append);
	printf("info->heredoc:[%s]\n", info->hdoc);
	printf("info->heredoc_txt:[%s]\n", info->hdoc_txt);
	printf("info->heredoc_cmd:[%s]\n", info->hdoc_cmd);
	printf("pipefd:[%d][%d]\n", info->pipefd[0], info->pipefd[1]);
	printf("==========================\n");
}
