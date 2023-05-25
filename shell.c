#include "main.h"

/**
 * shell -  shell loop
 * @inf: the parameter & return inf structure
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell(info_t *inf, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(inf);
		if (intractive(inf))
			print_prompt(inf);
		_eputchar(BUF_FLUSH);
		r = get_inp(inf);
		if (r != -1)
		{
			if (!set_info(inf, av))
			{
				builtin_ret = find_bltin(inf);
				if (builtin_ret == -1)
					find_cmd(inf);
			} else
				builtin_ret = -3;
		}
		else if (intractive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_hist(inf);
	free_info(inf, 1);
	if (!intractive(inf) && inf->status)
		exit(inf->status);
	if (builtin_ret <= -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_ret);
}

/**
 * find_bltin - It finds a builtin cmd
 * @inf: the parameter and return inf struct
 *
 * Return: -1 if bltin not found,
 *			0 if bltin executed successfully,
 *			1 if bltin found but not successful,
 *			-2 if bltin signals exit()
 */
int find_bltin(info_t *inf)
{
	int i, blt_in_ret = -1;
	bltin_table bltintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhist},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	if (inf->hdoc)
		return (0);
	for (i = 0; bltintbl[i].type; i++)
		if (_strcmp(inf->argv[0], bltintbl[i].type) == 0)
		{
			inf->line_count++;
			blt_in_ret = bltintbl[i].func(inf);
			break;
		}
	return (blt_in_ret);
}

/**
 * find_command - It finds a cmd in PATH
 * @inf: the parameter and return inf struct
 *
 * Return: void
 */
void find_command(info_t *inf)
{
	char *path = NULL;
	int i, k;

	inf->path = inf->argv[0];
	if (inf->linecountF == 1)
	{
		inf->line_count++;
		inf->linecountF = 0;
	}
	for (i = 0, k = 0; inf->arg[i]; i++)
		if (!is_deli(inf->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_command(inf);
	}
	else
	{
		if ((intractive(inf) || _getenv(inf, "PATH=")
			|| inf->argv[0][0] == '/') && find_command(inf, inf->argv[0]))
			fork_command(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_err(inf, "not found\n");
		}
	}
}

/**
 * fork_command - It forks an exec thread to run cmd
 * @inf: the parameter and return inf struct
 *
 * Return: void
 */
void fork_command(info_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->status));
		/*printf(CYN "WAIT DONE" RESL);*/
		if (inf->pipefd[1] > 2)
		{
			/*printf(RED "CLOSING WRITE PIPE" RESL);*/
			close(inf->pipefd[1]), inf->pipefd[1] = 0;
		}

		inf->left_redirect_from_fd = -1; /* RESET FD */
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_err(inf, "Permission denied\n");
		}
	}
}


/**
 * handle_redirects - It handles all left/right redirect syscalls
 * @inf: parameter struct
 */
void handle_redirects(info_t *inf)
{
	int pipefd[2];

	inf->dup_stdin = dup(STDIN_FILENO);
	inf->dup_stdout = dup(STDOUT_FILENO);
	if (inf->left_redirect_from_fd == DOC_FD)
	{
		if (pipe(pipefd) == -1)
			exit(1);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			exit(1);
		write(pipefd[1], inf->hdoc_txt, _strlen(inf->hdoc_txt));
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else if (inf->left_redirect_from_fd > -1)
	{
		if (dup2(inf->left_redirect_from_fd, STDIN_FILENO) == -1)
		{
			/* TODO: error msg? */
			exit(1);
		}
	}
	if (inf->right_redirect_to_fd > -1)
	{
		if (dup2(inf->right_redirect_to_fd, inf->right_redirect_from_fd) == -1)
		{
			/* TODO: error msg? */
			exit(1);
		}
	}
}
