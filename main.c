#include "main.h"

/**
* main - Entry point
* @ac: no of arguments.
* @av: Pointer to array
* Return: Always 0 if success else 1.
*/

int main(int ac, char *av[])
{
char **token;
char *line;
int stat;
(void)ac;
signal(SIGINT, ctr_lc);
stat = 0;
while (stat == 0)
{
prompt();
line = readLine();
if (str_cmp(line, "\n") == 0)
{
token = NULL;
free(line);
continue;
}
token = string_to_token(line);
if (token[0] == NULL)
{
free(token);
free(line);
continue;
}
if (str_cmp(token[0], "exit") == 0)
{
exit_shell(token, line);
}
else
{
stat =  exe_func(token, av[0]);
}
free(line);
free(token);
}
return (stat);
}
