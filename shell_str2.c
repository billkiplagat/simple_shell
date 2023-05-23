#include "main.h"

/**
 * str_dup - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *str_dup(const char *s)
{
char *new;
size_t len;

len = str_len(s);
new = malloc(sizeof(char) * (len + 1));
if (new == NULL)
return (NULL);
mem_cpy(new, s, len + 1);
return (new);
}

/**
 * str_len - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int str_len(const char *s)
{
int len;

for (len = 0; s[len] != 0; len++)
{
}
return (len);
}

/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char str[], const char *delim)
{
unsigned int i, j, k;

for (i = 0, k = 0; str[i]; i++)
{
for (j = 0; delim[j]; j++)
{
if (str[i] == delim[j])
{
k++;
break;
}
}
}
if (i == k)
return (1);
return (0);
}

/**
 * str_tok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *str_tok(char str[], const char *delim)
{
static char *split_str, *str_end;
char *str_start;
unsigned int i, bool;

if (str != NULL)
{
if (cmp_chars(str, delim))
return (NULL);
split_str = str;
i = str_len(str);
str_end = &str[i];
}
str_start = split_str;
if (str_start == str_end)
return (NULL);
for (bool = 0; *split_str; split_str++)
{
if (split_str != str_start)
if (*split_str && *(split_str - 1) == '\0')
break;
for (i = 0; delim[i]; i++)
{
if (*split_str == delim[i])
{
*split_str = '\0';
if (split_str == str_start)
str_start++;
break;
}
}
if (bool == 0 && *split_str)
bool = 1;
}
if (bool == 0)
return (NULL);
return (str_start);
}

/**
 * is_digit - defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int is_digit(const char *s)
{
unsigned int i;

for (i = 0; s[i]; i++)
{
if (s[i] < 48 || s[i] > 57)
return (0);
}
return (1);
}

