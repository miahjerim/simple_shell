#include "shell.h"
/**
 * shellhistory_file - finds history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */
char *shellhistory_file(info_t *info)
{
	char *buf, *dir;

/*get user's home directory from the environment variables*/
	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
		/*memoryallocation for the history file path*/
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
		/*Concatenate home directory, history file name to form path*/
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * shellhistory_write - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int shellhistory_write(info_t *info)
{
	ssize_t fd;
	char *filename = shellhistory_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

/*Open history file for writing, creating if does not exist*/
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);

		/*Iterate over history linked list and write each command to the file*/
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	/*Flush the buffer to the file*/
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_shellhistory_read - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int shellhistory_read(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = shellhistory_file(info);

	if (!filename)
		return (0);

/*Open the history file for reading*/
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);

		/*Get the size of the history file*/
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);

		/*Allocate memory for the buffer to store the file contents*/
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);

		/*Read the contents of the history file into the buffer*/
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);

		/*Process the buffer and create a linked list of history entries*/
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			shellhistory_creatlist(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		shellhistory_creatlist(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
 shellhistory_newnumber(info);
	return (info->histcount);
}

/**
 * shellhistory_creatlist - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int shellhistory_creatlist(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * shellhistory_newnumber - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int shellhistory_newnumber(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	for (; node; node = node->next, i++)
	{
		node->num = i;
	}
	return (info->histcount = i);
}