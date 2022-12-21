#include <stdio.h>

/**
 * _strlen - gets the length of a null byte terminated string
 * @s: string to check
 * Return: length of string
 */

int _strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}
