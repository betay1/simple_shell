#include "shell.h"

/**
 * interactive - true if shell is interactive
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if char is a delimeter
 * @c: char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
		return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic char
 *@c: character to input
 *Return: 1 if i is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts string to integer
 *@s: string to be converted
 *Return: 0 if no numbers, otherwise converted num
 */

int _atoi(char *s)
{
	int x, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (x = 0;  s[x] != '\0' && flag != 2; x++)
	{
		if (s[x] == '-')
			sign *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
