#include "shell.h"
/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int lenght = 0;

/*Check if the string is NULL*/
	if (!s)
		return (0);

/* Increment the pointer until reaching the end of the string*/
for (; *s != '\0'; s++)
		lenght++;
	return (lenght);
}
/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	/*Compare characters until reaching the end of either string
	{*/
	while (*s1 && *s2)
	{
		/*If characters are different, return the difference*/
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * needle_start - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *needle_start(const char *haystack, const char *needle)
{
	/*Iterate through the needle until reaching the end*/
	while (*needle)
	/*If characters are different, return NULL*/
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

/*Move the pointer to the end of the destination string*/
	while (*dest)
		dest++;
		/*Copy characters from src to dest until reaching the end of src*/
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}