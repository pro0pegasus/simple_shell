#include "main.h"

/**
 * clear_info - It initializes infot struct
 * @inf: struct address
 */
void clear_info(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
	if (inf->left_redirect_from_fd != DOC_FD)
	{
		/* TODO where else? - when to RESET? */
		inf->left_redirect_from_fd = -1;
	}
	inf->left_append = 0;
	inf->right_redirect_from_fd = 1;
	inf->right_redirect_to_fd = -1;
	inf->right_append = 0;
}

/**
 * set_info - It initializes info t struct
 * @inf: the struct address
 * @av: argument vector
 * Return: 0 if no error else err code
 */
int set_info(info_t *inf, char **av)
{
	int i = 0;

	inf->err_num = 0;
	inf->fname = av[0];
	if (inf->arg)
	{
		parse_redir_left(inf);
		parse_redir_right(inf);
		if (inf->left_redirect_from_fd == DOC_FD)
		{
			if (!inf->hdoc_cmd)
				inf->hdoc_cmd = _strdup(inf->arg);
		}
		handle_redirects(inf);
		inf->argv = strtow0(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		repl_alias(inf);
		repl_var(inf);
	}
	return (inf->err_num);
}

/**
 * free_info - It frees info t structure fields
 * @inf: structure address
 * @all: true if freeing all fields
 */
void free_info(info_t *inf, int all)
{
	rest_stdfd(inf);
	free(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (inf->left_redirect_from_fd > 2)
	{
		close(inf->left_redirect_from_fd);
		inf->left_redirect_from_fd = -1;
	}
	if (inf->right_redirect_to_fd > 2)
	{
		close(inf->right_redirect_to_fd);
		inf->right_redirect_to_fd = -1;
	}
	if (inf->hdoc_txt && inf->left_redirect_from_fd != DOC_FD)
		free((void **)&inf->hdoc_txt);
	if (all)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_lst(&(inf->env));
		if (inf->history)
			free_lst(&(inf->history));
		if (inf->alias)
			free_lst(&(inf->alias));
		free((void **)&inf->hdoc);
		free((void **)&inf->hdoc_txt);
		free((void **)&inf->hdoc_cmd);
		free(inf->environ);
			inf->environ = NULL;
		free((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		__get(-1);
		_putchar(BUF_FLUSH);
	}
}

/**
 * print_info - It prints info t structure
 * @inf:the struct address
 */
void print_info(info_t *inf)
{
	int i = 0;

	printf("inf->arg:[%s]\n", inf->arg);
	printf("inf->argv:%s\n", inf->argv ? "" : "[(null)]");
	for (i = 0; inf->argv && inf->argv[i]; i++)
		printf("\tinf->argv[%d]:[%s]\n", i, inf->argv[i]);
	printf("inf->path:[%s]\n", inf->path);
	printf("inf->argc:[%d]\n", inf->argc);
	printf("inf->line_count:[%d]\n", inf->line_count);
	printf("inf->err_num:[%d]\n", inf->err_num);
	printf("inf->status:[%d]\n", inf->status);
	printf("inf->fname:[%s]\n", inf->fname);
	printf("inf->env:[%p]\n", (void *)inf->env);
	printf("inf->cmd_buf:[%p]\n", (void *)inf->cmd_buf);
	printf("inf->*cmd_buf:[%s]\n",
	       inf->cmd_buf ? *(inf->cmd_buf) : "NONE");

	printf("inf->left_redirect_from_fd:[%d]\n", inf->left_redirect_from_fd);
	printf("inf->right_redirect_from_fd:[%d]\n", inf->right_redirect_from_fd);
	printf("inf->right_redirect_to_fd:[%d]\n", inf->right_redirect_to_fd);
	printf("inf->left_append:[%d]\n", inf->left_append);
	printf("inf->hdoc:[%s]\n", inf->hdoc);
	printf("inf->hdoc_txt:[%s]\n", inf->hdoc_txt);
	printf("inf->hdoc_cmd:[%s]\n", inf->hdoc_cmd);
	printf("pipefd:[%d][%d]\n", inf->pipefd[0], inf->pipefd[1]);
	printf("==========================\n");
}
