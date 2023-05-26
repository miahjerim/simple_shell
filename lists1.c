#include "shell.h"

/**
 * list_length - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		/* Move to the next node*/
		h = h->next;
		/*Increment the counter*/
		i++;
	}
	return (i);
}

/**
 * array_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **array_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_length(head), j;
	char **strs;
	char *str;

/*Check if the list is empty*/
	if (!head || !i)
		return (NULL);

		/*Allocate memory for the array of strings*/
	strs = malloc(sizeof(char *) * (i + 1));

	/*Check if memory allocation failed*/
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		/*Allocate memory for each string*/
		str = malloc(_strlen(node->str) + 1);

/*Check if memory allocation failed*/
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

/*Copy the string from the node to str*/
		str = _strcpy(str, node->str);
		/*Store the string in the array of strings*/
		strs[i] = str;
	}
	/*Add a NULL pointer at the end of the array*/
	strs[i] = NULL;
	return (strs);
}


/**
 * display_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t display_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		/*Print the value of num*/
		_puts(convert_number(h->num, 10, 0));

		_putchar(':');
		_putchar(' ');

		/*Print the string or "(nil)" if it's NULL*/
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;

		i++;/*Increment the counter*/
	}
	return (i);
}

/**
 * nodebegin_string - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nodebegin_string(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		/*Check if the string starts with the prefix*/
		p = starts_with(node->str, prefix);
		/*Check if the next character matches or c is -1*/
		if (p && ((c == -1) || (*p == c)))
			return (node);
			/*Move to the next node
    }*/
		node = node->next;
	}
	return (NULL);
}

/**
 * find_nodeindex - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t find_nodeindex(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		/*Check if the current node is the same as the given node*/
		if (head == node)
			return (i);

		head = head->next;
		i++;
	}
	
	return (-1);/*Return -1 if the node is not found*/
}