#include "shell.h"
/**
 * get_environ - returns the string array
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		/*Check if the environ variable is null or if there have been changes*/
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}
/**
 * _unsetenv - Remove environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

/*Check if the linked list or the variable is null*/
	if (!node || !var)
		return (0);

	while (node)
	{
		/*Check if the variable starts with the given var string*/
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			/*Delete the node at the current index and update info->env_changed*/
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;
/*Check if the variables are null*/
	if (!var || !value)
		return (0);

/*Allocate memory for the new variable string*/
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

		/*Copy the variable and value into the new string*/
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	/*Add a new node at the end of the linked list with the new variable string*/
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}