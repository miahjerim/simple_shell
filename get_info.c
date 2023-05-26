#include "shell.h"
/**
 * initialize_info - initializes info_t struct
 * @info: struct address
 */
void initialize_info(info_t *info)
{
	/*Set all fields of info_t struct to NULL*/
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * setinfo_struct - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void setinfo_struct(info_t *info, char **av)
{
	int i = 0;

/*Set the fname field of info_t to the first element of av*/
	info->fname = av[0];

	if (info->arg)
	/*Split the arg string into separate arguments using strtow function*/
	{
		
		info->argv = strtow(info->arg, " \t");

		if (!info->argv)
		{
			/*If strtow fails, allocate memory for a single-element argv array*/
			info->argv = malloc(sizeof(char *) * 2);

			if (info->argv)
			{
				/*Duplicate the arg string and assign it to the first element of argv*/
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		/*Count the number of arguments and assign it to argc*/
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

/*Call functions to replace aliases and variables in the arguments*/
		alias_redone(info);
		vars_redone(info);
	}
}
/**
 * field_freeinfo - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void field_freeinfo(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	/*If all flag is true, free additional fields and perform cleanup*/
	{
/*Free arg if cmd_buf is not set*/
		if (!info->cmd_buf)
			free(info->arg);

/*Free env, history, and alias linked lists*/	
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));

			/*Free environ array and set it to NULL*/
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		/*Free cmd_buf and set it to NULL*/
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}