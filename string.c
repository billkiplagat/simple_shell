#include "main.h"

/**
 * is_delimiter - Check if char is equal to delim.
 * @c: character.
 * @delim: " "
 * Return: 0 if no match, 1 if matched.
 */

int is_delimiter(char c, const char *delim)
{
while (delim && *delim)
{
if (c == *delim)
{
return (1);
}
++delim;
}
return (0);
}
/**
 * str_cat - Concatenates two strings.
 * @dest: Pointer to string to be conatenated upon.
 * @src: Pointer to string to append to dest.
 * Return: Pointer to dest.
 */
char *str_cat(char *dest, char *src)
{
char *address;
int len;

address = dest;
len = str_len(dest);
address = address + len;
while (*src != '\0')
{
*address = *src;
src++;
address++;
}
*address = '\0';

return (dest);
}

/**
 * check_white_space - checks for white space.
 * @s: Pointer to string to check.
 * Return: integer.
 */
unsigned int check_white_space(char *s)
{
int i = 0, count = 0;

while (s[i] != '\0')
{
if (s[i]  == ' ' || s[i] == '\t' || s[i] == '\n')
count++;
i++;
}
return (count);
}
/**
 * str_cmp - Compares two strings.
 * @s1: Pointer to First string.
 * @s2: Pointer to Second string.
 * Return: 0 if they are equal, Otherwise - positive value.
 */

int str_cmp(char *s1, char *s2)
{
int i = 0;

while (s1[i] != '\0' || s2[i] != '\0')
{
if (s1[i] != s2[i])
return (s1[i] - s2[i]);
i++;
}
return (0);
}
/**
 *ctr_lc - Control C handler.
 *@signum: The signal number received.
 *
 *Return: Void.
 */
void ctr_lc(int signum)
{
(void)signum;
write(STDOUT_FILENO, "$ ", 3);
}
