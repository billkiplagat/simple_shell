#include "main.h"

/**
* comment - deletes comments from the input
*
* @in: input string
* Return: input without comments
*/
char *comment(char *in)
{
int i, up_to;
up_to = 0;
for (i = 0; in[i]; i++)
{
if (in[i] == '#')
{
if (i == 0)
{
free(in);
return (NULL);
}
if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
up_to = i;
}
}
if (up_to != 0)
{
in = _realloc(in, i, up_to + 1);
in[up_to] = '\0';
}
return (in);
}

/**
* loop - Loop of shell
* @shell_data: data relevant (av, input, args)
*
* Return: no return.
*/
void loop(runtime_data *shell_data)
{
int loop, index;
char *input;
loop = 1;
while (loop == 1)
{
write(STDIN_FILENO, "($) ", 4);
input = readLine(&index);
if (index != -1)
{
input = comment(input);
if (input == NULL)
continue;
if (check_error(shell_data, input) == 1)
{
shell_data->status = 2;
free(input);
continue;
}
input = replace_var(input, shell_data);
loop = split_command(shell_data, input);
shell_data->counter += 1;
free(input);
}
else
{
loop = 0;
free(input);
}
}
}
