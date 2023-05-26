#include "shell.h"

/**
 * prompt - shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int prompt(info_t *info, char **av)
{
	ssize_t j = 0;
	int builtin_ret = 0;

	while (j != -1 && builtin_ret != -2)
	{
		/*display prompt*/
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);

		/*read users input*/
		j = get_input(info);
		if (j != -1)
		{
			set_info(info, av);/*set input info*/
			/*Check if the command is a built-in command*/
			builtin_ret = get_builtin(info);

			if (builtin_ret == -1)
				find_command(info);/*If not a built-in command, find and execute the command*/
		}

		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);/*Free memory allocated for the input information*/
	}
	write_history(info);/*Write command history to file*/
	free_info(info, 1);/*Free memory allocated for the input information*/

	if (!interactive(info) && info->status)
	/*If not running interactively and there was an error, exit with the error code*/
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
		/*If a built-in command signals an exit, exit with the shell's status code*/
			exit(info->status);
			/*If a built-in command signals a specific error code, exit with that error code*/
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * get_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int get_builtin(info_t *info)
{
	
	int k, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (k = 0; builtintbl[k].type; k++)
		if (_strcmp(info->argv[0], builtintbl[k].type) == 0)
		{
			info->line_count++;
			/*Call the appropriate built-in function*/
			built_in_ret = builtintbl[k].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * get_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void get_command(info_t *info)
{
	char *path = NULL;
	int l, m;

/*Set the command path to the argument itself*/
	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (l = 0, m = 0; info->arg[l]; l++)
		if (!is_delim(info->arg[l], " \t\n"))
			m++;
	if (!m)
		return;

/*Find the command in the directories listed in PATH
	if (path)*/
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;/*Set the command path to the found path*/
		fork_command(info);/*Execute the command*/
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))

			fork_command(info);
			/*If the command is not found but matches other conditions, execute it*/
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			/*Print error message if command not found*/
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork - forks cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

/*Fork a child process*/
	child_pid = fork();
	if (child_pid == -1)
	{
		/*Print error message if forking fails*/
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		/*Execute the command in the child process*/
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
			/*If permission denied, exit with code 126*/
				exit(126);
				/*If execution fails, exit with code 1*/
			exit(1);
		}
	}
	else
	{
		/*Wait for the child process to complete*/
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			/*Get the exit status of the child process*/
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
			/*Print error message if permission denied*/
				print_error(info, "Permission denied\n");
		}
	}
}