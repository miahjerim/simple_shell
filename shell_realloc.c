#include "shell.h"

/**
 * fill_memory - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *fill_memory(char *s, char b, unsigned int n)
{
	unsigned int i;
/*while loop iteration*/
	while(i < n)
	{
	s[i] = b;
	i++;
	}

	return (s);

}

/**
 * free_string - frees a string of strings
 * @pp: string of strings
 */
void free_string(char **pp)
{
	char **a = pp;

/*Check if 'pp' is NULL*/
	if (!pp)
		return;
		
		/*Loop until the value of the current string pointer is not NULL*/
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * memory_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *memory_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

/*Check if 'ptr' is NULL (no previous block was allocated)*/
	if (!ptr)
		return (malloc(new_size));
		/*Check if 'new_size' is 0 (new block should have size 0)*/
	if (!new_size)
		return (free(ptr), NULL);
		/*heck if 'new_size' = 'old_size' (no change in size)
		return (ptr);  // Return the pointer to the previous block without reallocation
*/
	if (new_size == old_size)
		return (ptr);

/*Allocate 'new_size' using malloc and assign the pointer to 'p'
	if (!p)  // Check if 'p' is NULL (malloc failed)*/
	p = malloc(new_size);
	if (!p)
		return (NULL);

/*Determine the smaller size between 'old_size' and 'new_size'*/
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);/*Free the previous block*/
	return (p);
}