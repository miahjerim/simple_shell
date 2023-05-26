#include "shell.h"
/**
 * chain_test - test if buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chain_test(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;
/*checking for chain delimiter: "||"*/ 
	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		/*set cmd_buf_type upto  CMD_OR*/
		info->cmd_buf_type = CMD_OR;
	}
	/*checking for chain delimiter: "&&"*/ 
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		/*set cmd_buf_type to CMD_AND*/
		info->cmd_buf_type = CMD_AND;
	}
	/*checking for chain delimiter: ";"*/ 
	else if (buf[j] == ';') /*end of command */
	{
		buf[j] = 0; /* update semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chain_check - checks chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
	* @len: length of buf
 * @p: address of current position in buf
 * @i: starting position in buf
 * 
 *
 * Return: Void
 */
void chain_check(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;
/*Check if previous command was CMD_AND and status is non-zero*/
	if (info->cmd_buf_type == CMD_AND)
	{

		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
		/*Check if previous command was CMD_OR and status is zero*/
	if (info->cmd_buf_type == CMD_OR)
	{

		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * alias_redone - replaces aliases in the tokenized string
 * @info: the parameter struct
	* 
 * Return: 1 if replaced, 0 otherwise
 */
int alias_redone(info_t *info)
{
	
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		/*Search for an alias that starts with the first argument*/
		node = node_starts_with(info->alias, info->argv[0], '=');

		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1)
		if (!p)
			return (0);
		info->argv[0] = p;
	}

	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int vars_redone(info_t *info)
{
	int i = 0;

	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
		 string_redone(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}

		if (!_strcmp(info->argv[i], "$$"))
		{
		 string_redone(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');

		if (node)
		{
		 string_redone(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
	 string_redone(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * string_redone - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int string_redone(char **old, char *new)
{
	free(*old);

	*old = new;

	return (1);
}