#include "shell.h"

/**
 * freepointer - frees a pointer set address to NULL
 * @ptr: address of the pointer
 *
 * Return: 1 if freed, 0 otherwise.
 */
int freepointer(void **ptr)
{
/*checks if ptr is not NULL and if the pointer it points to (*ptr) is also not NULL.*/
	if (ptr && *ptr)
	{
		free(*ptr);
		/*After freeing the memory, the pointer *ptr is set to NULL using the assignment*/
		*ptr = NULL;
		return (1);
	}

	return (0);

}
