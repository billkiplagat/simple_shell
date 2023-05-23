#include "main.h"

/**
 * readLine - reads the input string.
 *
 * @val: return value of getline function
 * Return: input string
 */
char *readLine(int *val)
{
char *input = NULL;
size_t buffer_size = 0;

*val = getline(&input, &buffer_size, stdin);
return (input);
}
