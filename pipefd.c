#include "main.h"

/**
 * open_pipe - It handles the inter process comm
 * @info: the parameter struct
 */
void open_pipefd(info_t *inf)
{
	/*printf(BLU "OPEN_PIPE()" RESL);*/
	if (!inf->pipefd[0] && !inf->pipefd[1])
	{
		if (pipe(inf->pipefd) == -1)
			exit(1);
		/*printf(RED "NEW PIPE %d:%d" RESL, info->pipefd[0], info->pipefd[1]);*/
	}
	/* set right redirect to write-end of pipe */
	inf->right_redirect_to_fd = inf->pipefd[1];
}
