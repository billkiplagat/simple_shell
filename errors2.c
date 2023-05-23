#include "main.h"

/**
* env_err - error message for env in get_env.
* @shell_data: data relevant (counter, arguments)
* Return: error message.
*/
char *env_err(runtime_data *shell_data)
{
int len;
char *error;
char *ver_str;
char *message;

ver_str = _itoa(shell_data->counter);
message = ": Unable to add/remove from environment\n";
len = str_len(shell_data->av[0]) + str_len(ver_str);
len += str_len(shell_data->args[0]) + str_len(message) + 4;
error = malloc(sizeof(char) * (len + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}

str_cpy(error, shell_data->av[0]);
str_cat(error, ": ");
str_cat(error, ver_str);
str_cat(error, ": ");
str_cat(error, shell_data->args[0]);
str_cat(error, message);
str_cat(error, "\0");
free(ver_str);

return (error);
}
/**
* path_err - error message for path and failure denied permission
* @shell_data: data relevant (counter, arguments).
*
* Return: The error string.
*/
char *path_err(runtime_data *shell_data)
{
int len;
char *ver_str;
char *error;

ver_str = _itoa(shell_data->counter);
len = str_len(shell_data->av[0]) + str_len(ver_str);
len += str_len(shell_data->args[0]) + 24;
error = malloc(sizeof(char) * (len + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}
str_cpy(error, shell_data->av[0]);
str_cat(error, ": ");
str_cat(error, ver_str);
str_cat(error, ": ");
str_cat(error, shell_data->args[0]);
str_cat(error, ": Permission denied\n");
str_cat(error, "\0");
free(ver_str);
return (error);
}
