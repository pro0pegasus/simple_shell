#include "main.h"

/**
 * is_valid_path - a short descrip
 *
 * Description: a long descrip
 *
 * @filename: str
 *
 * Return: 1 is execu 0 is non execu
 */
int is_valid_path(char *filename)
{
	size_t length = strlen(filename);

	if (length >= strlen("../"))
		if (strncmp(filename, "../", strlen("../")) == 0)
			return (1);
	if (length >= strlen("./"))
		if (strncmp(filename, "./", strlen("./")) == 0)
			return (1);
	if (length >= strlen("/"))
		if (strncmp(filename, "/", strlen("/")) == 0)
			return (1);
	return (0);
}

/**
 * filepath_creator - a short descrip
 *
 * Description: a long descrip
 *
 * @file_path: arg_1 descrip
 * @array_of_tokens: arg_2 descrip
 * @filename: file name str
 * @token_index: index to cpy
 *
 * Return: void
 */
void filepath_creator(char **file_path, char **array_of_tokens,
		char *filename, int token_index)
{
	malloc_char(file_path,
			(strlen(array_of_tokens[token_index]) + strlen(filename) + 2),
			"_which Error: malloc failed for file_path");
	strcpy(*file_path, array_of_tokens[token_index]);
	strcat(*file_path, "/");
	strcat(*file_path, filename);
	strcat(*file_path, "\0");
}

/**
 * _which - a short descrip
 *
 * Description: a long descrip
 *
 * @filename: arg_1 descrip
 *
 * Return: return descrip
 */
char *_which(char *filename)
{
	struct stat sb;
	char *path_var, *delimiter, *file_path;
	char **array_of_tokens;
	int token_index, file_path_exist;

	delimiter = ":";
	path_var = _getenv("PATH");
	if (path_var != NULL)
	{
		array_of_tokens = array_maker(path_var, delimiter);
		if (array_of_tokens != NULL)
		{
			for (token_index = 0; array_of_tokens[token_index]; token_index++)
			{
				filepath_creator(&file_path, array_of_tokens, filename, token_index);
				file_path_exist = stat(file_path, &sb);
				if (file_path_exist == 0)
				{
					free_which(&path_var, array_of_tokens);
					return (file_path);
				}
				free(file_path);
			}
			free_which(&path_var, array_of_tokens);
		}
		else
			free(path_var);
	}
	file_path_exist = stat(filename, &sb);
	if (file_path_exist == 0 && is_valid_path(filename))
		return (strdup(filename));
	return (NULL);
}
