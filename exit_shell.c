#include "main.h"

/**
* exit_shell - exits the shell
*
* @shell_data: data
* Return: 0
*/
int exit_shell(runtime_data *shell_data)
{
int number;
unsigned int c_status;
int digit;
int strlen;
if (shell_data->args[1] != NULL)
{
c_status = _atoi(shell_data->args[1]);
digit = is_digit(shell_data->args[1]);
strlen = str_len(shell_data->args[1]);
number = c_status > (unsigned int)INT_MAX;
if (!digit || strlen > 10 || number)
{
get_error(shell_data, 2);
shell_data->status = 2;
return (1);
}
shell_data->status = (c_status % 256);
}
return (0);
}
