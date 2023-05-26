#include "shell.h"
/**
 * interactive - returns true if interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	/*Check if stdin is associated with a terminal and if readfd is a valid file descriptor*/
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - checks delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	/*Iterate through each character in the delimiter string*/
	while (*delim)

	/*If the current character matches the given character, return true*/
		if (*delim++ == c)
			return (1);

			/*If no match is found, return false*/
	return (0);
}
/**
 * _isalpha - check alphabetic
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	/*Check if the character is within the ASCII range of lowercase or uppercase letters*/
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts string to integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	/*Iterate through each character in the string*/
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		/*Handle the sign of the number*/
		if (s[i] == '-')
			sign *= -1;

/*Convert the character to a digit if it is between '0' and '9'*/
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		/*If a digit has already been encountered, break the loop*/
		else if (flag == 1)
			flag = 2;
	}
/*Apply the sign to the result*/
	if (sign == -1)
		output = -result;
	else
	/*Return the converted integer value*/
		output = result;

	return (output);
}