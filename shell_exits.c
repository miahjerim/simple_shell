#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;
	char *s = dest;
for (i = 0; src[i] != '\0' && i < n - 1; i++)
{
	/*Copy the character from src to dest*/
	dest[i] = src[i];
}
if (i < n)
{
	int j;
	for (j = i; j < n; j++)
	{
		/*Fill the remaining characters in dest with null terminators*/
		dest[j] = '\0';
	}
	
}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	/*Find the end of the destination string*/
	while (dest[i] != '\0')
		i++;

		/*Append characters from src to dest, up to n bytes*/
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;

		/*Add null terminator if there is space remaining in dest*/
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	/*Iterate through each character of s*/
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
	}
	s++;

	return (NULL);
}