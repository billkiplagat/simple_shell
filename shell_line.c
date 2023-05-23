#include "main.h"

/**
 * bringLine - assigns the line var for get_line
 * @input_str: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void bringLine(char **input_str, size_t *n, char *buffer, size_t j)
{
if (*input_str == NULL)
{
if  (j > MAIN_BUFFER)
*n = j;
else
*n = MAIN_BUFFER;
*input_str = buffer;
}
else if (*n < j)
{
if (j > MAIN_BUFFER)
*n = j;
else
*n = MAIN_BUFFER;
*input_str = buffer;
}
else
{
str_cpy(*input_str, buffer);
free(buffer);
}
}
/**
 * get_line - Read inpt from stream
 * @input_str: buffer that stores the input
 * @n: size of input_str
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **input_str, size_t *n, FILE *stream)
{
int i;
static ssize_t input;
ssize_t val;
char *buffer;
char t = 'z';

if (input == 0)
fflush(stream);
else
return (-1);
input = 0;

buffer = malloc(sizeof(char) * MAIN_BUFFER);
if (buffer == 0)
return (-1);
while (t != '\n')
{
i = read(STDIN_FILENO, &t, 1);
if (i == -1 || (i == 0 && input == 0))
{
free(buffer);
return (-1);
}
if (i == 0 && input != 0)
{
input++;
break;
}
if (input >= MAIN_BUFFER)
buffer = _realloc(buffer, input, input + 1);
buffer[input] = t;
input++;
}
buffer[input] = '\0';
bringLine(input_str, n, buffer, input);
val = input;
if (i != 0)
input = 0;
return (val);
}
