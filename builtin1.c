#include "shell.h"

/**
 * _myhistory - displays history list, one command by line
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	/*Print the history list of commands*/
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

/*Find the '=' character in the string*/
	p = _strchr(str, '=');
	if (!p)
		return (1);/*If '=' is not found, return error*/

	c = *p;
	*p = 0;

	/*Delete the node in the alias list that starts with the given alias string*/
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;

	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

/* Find the '=' character in the string*/
	p = _strchr(str, '=');
	if (!p)

		return (1);/*If '=' is not found, return error*/
	if (!*++p)
		return (unset_alias(info, str));/*If there is no value after '=', unset the alias*/

/*Unset the alias if it already exists*/
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');/*Find the '=' character in the alias string*/
		for (a = node->str; a <= p; a++)
		_putchar(*a);/*Print the alias name*/
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);

	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			/*Print all the aliases in the alias list*/
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		/*Find the '=' character in each argument
        if (p)*/
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
			
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}