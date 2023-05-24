#include "main.h"

/**
 * _putchar - Writes the character c to stdout.
 * @c: The character to print.
 * Return: On success - 1.
 */
int _putchar(char c)
{
return (write(1, &c, 1));
}

/**
 * string_to_token - splits a string into words.
 * @str: Pointer to string.
 * Return: Pointer to array of words.
 */
char **string_to_token(char *str)
{
int i = 0;
const char delim[] = " \t\n";
int sp = check_white_space(str);
char **tokens = malloc(sizeof(char *) * (sp + 1));
char *token;

if (!tokens)
{
free(tokens);
fprintf(stderr, "Allocation Error\n");
exit(1);
}

token = strtok(str, delim);
while (token != NULL)
{
tokens[i] = token;
token = strtok(NULL, delim);
i++;
}
tokens[i] =  NULL;

return (tokens);
}

/**
 * _atoi - Custom atoi converts string to int.
 * @s: string.
 * Return: Number if success, -1 if string contains non-numbers.
 */
int _atoi(char *s)
{
int i = 0;
unsigned int number = 0;

while (s[i] != '\0')
{
if (s[i] >= '0' && s[i] <= '9')
number = number * 10 + (s[i] - '0');
if (s[i] > '9' || s[i] < '0')
return (-1);
i++;
}
return (number);
}
/**
 * _puts - prints a string, followed by a new line, to stdout.
 * @str: string to print.
 */

void _puts(char *str)
{
unsigned long i = 0;

while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
_putchar('\n');
}
