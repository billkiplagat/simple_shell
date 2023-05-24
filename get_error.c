#include "main.h"

/**
* get_error - calls the error according the builtin, syntax or permission
* @shell_data: data containing arguments
* @error_value: error value
* Return: error
*/
int get_error(runtime_data *shell_data, int error_value)
{
char *error;

switch (error_value)
{
case -1:
error = env_err(shell_data);
break;
case 126:
error = path_err(shell_data);
break;
case 127:
error = notfound_err(shell_data);
break;
case 2:
if (str_cmp("exit", shell_data->args[0]) == 0)
error = exit_err(shell_data);
else if (str_cmp("cd", shell_data->args[0]) == 0)
error = get_cd_err(shell_data);
break;
}

if (error)
{
write(STDERR_FILENO, error, str_len(error));
free(error);
}

shell_data->status = error_value;
return (error_value);
}
