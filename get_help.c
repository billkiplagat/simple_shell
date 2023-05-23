#include "main.h"

/**
* get_help - function that retrieves help messages according builtin
* @shell_data: data structure (args and input)
* Return: Return 1
*/
int get_help(runtime_data *shell_data)
{
if (shell_data->args[1] == 0)
help_general();
else if (str_cmp(shell_data->args[1], "exit") == 0)
help_exit();
else if (str_cmp(shell_data->args[1], "cd") == 0)
cd_help();
else if (str_cmp(shell_data->args[1], "setenv") == 0)
help_setenv();
else if (str_cmp(shell_data->args[1], "alias") == 0)
alias_help();
else if (str_cmp(shell_data->args[1], "unsetenv") == 0)
help_unsetenv();
else if (str_cmp(shell_data->args[1], "help") == 0)
builtin_help();
else if (str_cmp(shell_data->args[1], "env") == 0)
help_env();
else
write(STDERR_FILENO, shell_data->args[0],
str_len(shell_data->args[0]));
shell_data->status = 0;
return (1);
}
