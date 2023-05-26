#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)

{
	int i = 0;

	unsigned long int result = 0;

	if (*s == '+')
		s++;  

	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * display_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void display_error(info_t *info, char *estr)
{
	/* Print the file name */
	_eputs(info->fname);

	_eputs(": ");
	/* Print the line number */
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	/* Print the command name */
	_eputs(info->argv[0]);
	_eputs(": ");
	/* Print the specified error string */
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)

{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

/* Use error putchar if writing to stderr */
	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		/* Print '-' sign for negative numbers */
		__putchar('-');
		count++;
	}

	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			/* Print each digit */
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	/* Print the last digit */
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * cnvrt_num - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *cnvrt_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		/* Store the '-' sign for negative numbers */
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		/* Convert each remainder to a character */
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
	/* Add the '-' sign if necessary */
		*--ptr = sign;

	return (ptr);
}

/**
 * replace_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void replace_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			/* Replace '#' with '\0' */
			buf[i] = '\0';
			break;
		}
}