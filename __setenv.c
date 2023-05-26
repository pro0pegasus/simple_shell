#include "main.h"

/**
 * create_envar - a short descrip
 *
 * Description: a long descrip
 *
 * @env_var: arg_1 descrip
 * @envar_length: arg_2 descrip
 * @name: name str
 * @value: value str
 *
 * Return: return descrip
 */
void create_envar(char **env_var, unsigned int envar_length, const char *name,
		const char *value)
{
	*env_var = malloc_char(env_var, envar_length,
			"_setenv() Error: env_var malloc failed");
	envar_length = strlen(name) + strlen(value) + 2;
	*env_var = malloc_char(env_var, envar_length,
			"_setenv() Error: env_var malloc failed");
	strcpy(*env_var, name);
	strcat(*env_var, "=");
	strcat(*env_var, value);
	strcat(*env_var, "\0");
}

/**
 * _env_set_exists - a short descrip
 *
 * Description: a long descrip
 *
 * @env_var: arg_1 descrip
 * @envar_length: arg_2 descrip
 * @name: name str
 * @overwrite: overwrite intg
 *
 * Return: return descrip
 */
int _env_set_exists(char *env_var, unsigned int envar_length, const char *name,
		int overwrite)
{
	unsigned int env_index;

	for (env_index = 0; __environ[env_index]; env_index++)
	{
		if (strncmp(__environ[env_index], name, strlen(name)) == 0 && overwrite != 0)
		{
			free(__environ[env_index]);
			__environ[env_index] = malloc(sizeof(char) * envar_length);
			if (__environ[env_index] == NULL)
			{
				perror("_setenv() Error: __environ[env_index] malloc failed");
				free(env_var);
				return (-1);
			}
			strcpy(__environ[env_index], env_var);
			free(env_var);
			return (0);
		}
	}
	return (0);
}

/**
 * env_does_not_exists - a short descrip
 *
 * Description: a long descrip
 *
 * @env_var: arg_1 descrip
 * @envar_length: arg_2 descrip
 * @env_length: length of env
 *
 * Return: return descrip
 */
int env_does_not_exists(char *env_var, unsigned int envar_length,
		unsigned int env_length)
{
	unsigned int free_new_env_index;
	char **new_environ;

	new_environ = (char **) malloc(sizeof(char *) * (env_length + 2));
	if (new_environ == NULL)
	{
		perror("_setenv() Error: new_environ malloc failed");
		free(env_var);
		return (-1);
	}
	copy_array(new_environ, __environ);
	new_environ[env_length] = malloc(sizeof(char) * envar_length);
	if (new_environ[env_length] == NULL)
	{
		perror("_setenv() Error: new_environ[env_index] malloc failed");
		for (free_new_env_index = 0; free_new_env_index < env_length;
				free_new_env_index++)
			free(new_environ[free_new_env_index]);
		free(new_environ);
		free(env_var);
		return (-1);
	}
	strcpy(new_environ[env_length], env_var);
	new_environ[env_length + 1] = NULL;
	free(env_var);
	__environ = new_environ;
	return (0);
}

/**
 * _setenv - a short descrip
 *
 * Description: The setenv() func adds a var name to the
 * env with the value, if name does not already exist.
 * If name exists in the env, its value is changed
 * to value if overwrite is  not a zero; if overwrite is 0, then the
 * value the name isn't changed.
 * This funct makes copies of the strs pointed to by a name, and
 * the value. The unsetenv() func deletes
 * the var name from the envir. If name exists in the
 * envi, the func succeeds, the env is unchanged.
 *
 * @name: name str
 * @value: value str
 * @overwrite: overwrite intger
 *
 * Return: -1 on failure 0 on success
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	unsigned int envar_length;
	char *env_var;

	envar_length = strlen(name) + strlen(value) + 2;
	create_envar(&env_var, envar_length, name, value);
	_env_set_exists(env_var, envar_length, name, overwrite);
	if (_env_name_exists(name) != -1)
		_env_set_exists(env_var, envar_length, name, overwrite);
	else
		env_does_not_exists(env_var, envar_length, _env_length());
	return (0);
}
