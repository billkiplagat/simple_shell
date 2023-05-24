#include "main.h"

/**
 * readLine - Gets a typed line from the command line as a string.
 * Return: Pointer to the line(string).
 */

char *readLine(void)
{
char *line =  NULL;
size_t length = 0;
ssize_t characters = 0;

characters = getline(&line, &length, stdin);
if (characters == EOF)
{
free(line);
exit(0);
}
if (line == NULL)
{
write(STDOUT_FILENO, "\n", 1);
free(line);
exit(-1);
}
return (line);
}
