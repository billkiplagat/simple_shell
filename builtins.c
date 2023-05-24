#include "main.h"


/**
*print_env - Prints variables
*
* Return: void.
*/
void print_env(void)
{
int j = 0;

while (environ[j])
{
_puts(environ[j]);
j++;
}
}

/**
* _builtins - Checks if token
* @string: Pointer to string
* Return: 0 or 1.
*/
int _builtins(char *string)
{
if ((str_cmp(string, "env")) == 0)
{
return (0);
}
if ((str_cmp(string, "exit")) == 0)
return (0);
if ((str_cmp(string, "setenv")) == 0)
return (0);
if ((str_cmp(string, "unsetenv")) == 0)
return (0);
if ((str_cmp(string, "cd")) == 0)
return (0);
return (1);
}
/**
* exec_builtin - Executes function
* @tokens: Double pointer
* Return: 0
*/
int exec_builtin(char **tokens)
{
int i;

if ((str_cmp(*tokens, "cd")) == 0)
{
i = (change_dir(tokens));
(void)i;
return (0);
}
if ((str_cmp(*tokens, "env")) == 0)
{
print_env();
return (0);
}
if ((str_cmp(*tokens, "setenv")) == 0)
{
if (tokens[1] && tokens[2])
{
set_env(tokens[1], tokens[2]);
return (0);
}
printf("Usage: setenv var_name var_value\n");
return (0);
}
if (str_cmp(*tokens, "unsetenv") == 0)
{
if (tokens[1])
{
unset_env(tokens[1]);
return (0);
}
printf("Usage: unsetenv VAR_NAME\n");
return (0);
}
return (1);
}
/**
* exit_shell - Exits the shell
* @tokens: Double pointer
* @line: Pointer to string
* Return: void.
*/
void exit_shell(char **tokens, char *line)
{
int stat;

if (tokens[1] != NULL)
{
stat = atoi(tokens[1]);
if (stat >= 0)
{
free(line);
free(tokens);
exit(stat);
}
write(STDERR_FILENO, "Exit: illegal exit status: ", 28);
write(STDERR_FILENO, tokens[1], 1);
write(STDERR_FILENO, "\n", 1);
}
else
{
free(line);
free(tokens);
exit(0);
}
}
