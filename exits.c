#include "shell.h"

/**
 **_strncpy - copy string
 *@dest: destination string to be copied to
 *@src: source string
 *@n: amount of char to be copied
 *Return: concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
		dest[y] = '\0';
		y++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be maximally used
 *Return: concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < n)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < n)
		dest[x] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in the string
 *@s: string to be parsed
 *@c: character nedded
 *Return: (s) pointer to the memory area s
 */

char *_strchr(char *s, char c)
{
	do {
	if (*s == c)
		return (s);
	} while (*s++ != '\0');

	return (NULL);
}
