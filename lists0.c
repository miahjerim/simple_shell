#include "shell.h"

/**
 * addnode_start - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *addnode_start(list_t **head, const char *str, int num)
{
	list_t *new_head;

/*Check if head pointer is NULL*/
	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	/*Check if memory allocation failed*/
	if (!new_head)
		return (NULL);

		/*Initialize the new node*/
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		/*Duplicate the string and store it in the new node*/
		new_head->str = _strdup(str);

		if (!new_head->str)/*Check if string duplication failed*/
		{
			free(new_head);
			return (NULL);
		}
	}
	/*Update pointers to insert the new node at the start of the list*/
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * addnode_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *addnode_end(list_t **head, const char *str, int num)
{
	/*Check if head pointer is NULL*/
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	/*Allocate memory for a new node*/
	new_node = malloc(sizeof(list_t));

	if (!new_node)/*Check if memory allocation failed*/
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;


	if (str)
	{
		/*Duplicate the string and store it in the new node*/
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		/*Traverse the list to find the last node*/
		while (node->next)
			node = node->next;

			/*Update pointers to insert the new node at the end of the list*/
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * printlist_string - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printlist_string(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		/*Print the string of each node*/
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * deleteindex_node - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deleteindex_node(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

/*Check if head pointer or list is empty*/
	if (!head || !*head)
		return (0);

	if (!index)
	{
		/*Special case: Deleting the head node*/
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	/*Traverse the list to find the node at the given index*/
	while (node)
	{
		if (i == index)
		/*Update pointers to skip the node to be deleted*/
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);/*Node not found at the given index*/
}

/**
 * free_nodelist - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_nodelist(list_t **head_ptr)
{
	list_t *node, *next_node, *head;


/*Check if head pointer or list is empty*/
	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;

	/*Traverse the list and free memory for each node and its string*/
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);

		node = next_node;
	}

	*head_ptr = NULL;
	
}