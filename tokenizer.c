#include "shell.h"
/**
 * **split_string_0 - splits a string into words.
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string_0(char *str, char *d)
{
	int n, l, p, k, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
		/*If delimiter is not provided, default to " "*/
	if (!d)
		d = " ";

/*Count the number of words in the input string*/
	for (n = 0; str[n] != '\0'; n++)
		if (!is_delim(str[n], d) && (is_delim(str[n + 1], d) || !str[n + 1]))
			numwords++;

/*If there are no words, return NULL*/
	if (numwords == 0)
		return (NULL);

		/*Allocate memory for the array of strings*/
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

		/*Allocate memory for the array of strings*/
	for (n = 0, l = 0; l < numwords; l++)
	{
		/*Skip delimiter characters*/
		while (is_delim(str[n], d))
			n++;

			/*Extract the word by iterating until the next delimiter or end of string*/
		p = 0;
		while (!is_delim(str[n + p], d) && str[n + p])
			p++;

			/*Allocate memory for the word string*/
		s[l] = malloc((p + 1) * sizeof(char));
		if (!s[l])
		{
			/*Free previously allocated memory and return NULL if allocation fails*/
			for (p = 0; p < l; p++)
				free(s[p]);
			free(s);
			return (NULL);
		}
		/*Copy the word into the allocated string*/
		for (k = 0; k < p; k++)
			s[l][k] = str[n++];
		s[l][k] = 0;
	}
	s[l] = NULL;
	return (s);
}



/**
 * **split_string_1 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string_1(char *str, char d)
{
	int n, l, p, k, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

		/*Count the number of words in the input string*/
		if (!d)
		d = " ";
	while (str[n] != '\0')
	{
		if (!is_delim(str[n], d) && (is_delim(str[n + 1], d) || !str[n + 1]))
			numwords++;
			n++;
	}

			/* If there are no words, return NULL*/
	if (numwords == 0)
		return (NULL);

		/*Allocate memory for the array of strings*/
	s = malloc((1 + numwords) * sizeof(char *));

	if (!s)
		return (NULL);
	for (n = 0, l = 0; l < numwords; l++)
	{
		while (str[n] == d && str[n] != d)
			n++;

		p = 0;

		while (str[n + p] != d && str[n + p] && str[n + p] != d)
			p++;
		s[l] = malloc((p + 1) * sizeof(char));
		if (!s[l])
		{
			for (p = 0; p < l; p++)
				free(s[p]);
			free(s);
			return (NULL);
		}

		for (k = 0; k < p; k++)
			s[l][k] = str[n++];
		s[l][k] = 0;
	}
	s[l] = NULL;
	return (s);
}