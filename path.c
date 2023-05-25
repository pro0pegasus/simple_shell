#include "main.h"

/**
 * is_command - see if file is an executable
 * @path: file path
 * @inf: info struct
 * Return: 0 if false, otherwise 1
 */
int is_command(info_t *inf, char *path)
{
	struct stat sta;

	(void)inf;
	if (stat(path, &sta) || !path)
		return (0);
	else if (sta.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * dupl_char - character duplicator
 * @star: start of index
 * @stopp: stop of index
 * @pstri: string of path
 * Return: buffer pointer
 */

char *dupl_char(char *pstri, int stopp, int star)
{
	int j = 0, i = 0;
	static char buf[1024];

	for (i = 0, j = star; j < stopp; j++)
		if (pstri[j] != ':')
			buf[i++] = pstri[j];
	buf[i] = 0;
	return (buf);
}

/**
 * find_path - find command in the string of the path
 * @pstri: string of path
 * @cmd: the find command
 * @inf: the struct of the info
 * Return: NULL or the path of the command
 */
char *find_path(info_t *inf, char *cmd, char *pstri)
{
	int j = 0, posi_cur = 0;
	char *path;

	if (!pstri)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_command(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pstri[j] || pstri[j] == ':')
		{
			path = dupl_char(pstri, posi_cur, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_command(inf, path))
				return (path);
			if (!pstri[j])
				break;
			posi_cur = j;
		}
		j++;
	}
	return (NULL);
}
