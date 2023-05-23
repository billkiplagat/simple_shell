#include "main.h"
/**
* execute_line - finds builtins and commands
*
* @shell_data: data relevant (args)
* Return: 1 on success.
*/
int execute_line(runtime_data *shell_data)
{
int (*builtin)(runtime_data *shell_data);
if (shell_data->args[0] == NULL)
return (1);
builtin = built_in(shell_data->args[0]);
if (builtin != NULL)
return (builtin(shell_data));
return (execute_cmd(shell_data));
}
