#include "shell.h"
/**
 * cmd_exe_file - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int cmd_exe_file(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	/*Check if 'path' is NULL or if stat fails*/
	if (!path || stat(path, &st))
		return (0);


/*Check if the file is a regular file*/
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);/*File is not an executable command*/
}
/**
 * copy_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *copy_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;


/*Copy characters from 'pathstr' to 'buf' starting from 'start' index*/
	for (k = 0, i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
		{
			buf[k++] = pathstr[i];/* character to buffer*/
		}
	buf[k] = 0;/*null terminator to the buffer*/
	return (buf);
	}
}
/**
 * get_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *get_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;


/* If 'pathstr' is NULL, return NULL*/
	if (!pathstr)
		return (NULL);

/*is command starting with './' and is a file in the current directory*/
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{

		if (cmd_exe_file(info, cmd))
			return (cmd);/*Return the command as it is an executable
    }*/
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			/*get directory from 'pathstr'
*/
			path = copy_chars(pathstr, curr_pos, i);
			/*If the extracted directory is empty, append the command to it*/
			if (!*path)
				_strcat(path, cmd);

			else
			{
				/*Append '/' to the directory*/
				_strcat(path, "/");
				/* Append the command to the directory*/
				_strcat(path, cmd);
			}

			/*Check if the constructed path is an executable command*/
			if (cmd_exe_file(info, path))
				return (path);

				/*If the end of 'pathstr' is reached*/
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		
		i++;/*Move to the next character in 'pathstr'*/
	}
	return (NULL);
}