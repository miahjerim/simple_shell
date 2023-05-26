#include "shell.h"
/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{

	int n = 0;

	if (dest == src || src == 0)
		return (dest);

		/*Iterate over each character of the source string*/
		for (int n = 0; src[n] != '\0'; n++)
		{
			dest[n] = src[n];
		}
/*Add null terminator to the end of the destination string*/
	dest[n] = 0;
	return (dest);
}
/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

		/*Calculate the length of the string*/
	while (*str++)
		length++;

		/*Allocate memory for the duplicated string*/
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
		/*Copy each character from the original string to the new string in reverse order*/
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}
/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int n = 0;

	if (!str)
		return;

		/*Iterate over each character of the string*/
	while (str[n] != '\0')
	{
		/*Call _putchar to print each character*/
		_putchar(str[n]);
		n++;
	}
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

/*Flush the buffer or reset the buffer size if it's full or a special constant is encountered*/
	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buf, n);
		n = 0;
	}
	/*If the character is not a special constant, add it to the buffer*/
	if (c != BUF_FLUSH)
		buf[n++] = c;

	return (1);
}