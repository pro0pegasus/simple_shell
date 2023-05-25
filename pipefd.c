#include "main.h"

/**
 * open_pipefd - It handles the inter process comm
 * @inf: the parameter struct
 */
void open_pipefd(info_t *inf)
{
	/*printf(BLU "OPEN_PIPE()" RESL);*/
	if (!inf->pipefd[0] && !inf->pipefd[1])
	{
		if (pipe(inf->pipefd) == -1)
			exit(1);
		/*printf(RED "NEW PIPE %d:%d" RESL, inf->pipefd[0], inf->pipefd[1]);*/
	}
	/* set right redirect to write-end of pipe */
	inf->right_redirect_to_fd = inf->pipefd[1];
}
