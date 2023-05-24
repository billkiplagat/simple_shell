#include "main.h"

/**
* str_cat_cd - function that concatenates error msg
*
* @shell_data: data input
* @message: message to print
* @err: output error msg
* @ver_str: counter lines
* Return: error message
*/

char *str_cat_cd(runtime_data *shell_data, char *message,
char *err, char *ver_str)
{
char *illegal_flag;

str_cpy(err, shell_data->av[0]);
str_cat(err, ": ");
str_cat(err, ver_str);
str_cat(err, ": ");
str_cat(err, shell_data->args[0]);
str_cat(err, message);
if (shell_data->args[1][0] == '-')
{
illegal_flag = malloc(3);
illegal_flag[0] = '-';
illegal_flag[1] = shell_data->args[1][1];
illegal_flag[2] = '\0';
str_cat(err, illegal_flag);
free(illegal_flag);
}
else
{
str_cat(err, shell_data->args[1]);
}

str_cat(err, "\n");
str_cat(err, "\0");
return (err);
}

/**
* get_cd_err - error message for cd command in get_cd
* @shell_data: data
* Return: Error message
*/

char *get_cd_err(runtime_data *shell_data)
{
int len, len_id;
char *err, *ver_str, *message;

ver_str = _itoa(shell_data->counter);
if (shell_data->args[1][0] == '-')
{
message = ": Illegal option ";
len_id = 2;
}
else
{
message = ": can't cd to ";
len_id = str_len(shell_data->args[1]);
}

len = str_len(shell_data->av[0]) + str_len(shell_data->args[0]);
len += str_len(ver_str) + str_len(message) + len_id + 5;
err = malloc(sizeof(char) * (len + 1));

if (err == 0)
{
free(ver_str);
return (NULL);
}

err = str_cat_cd(shell_data, message, err, ver_str);

free(ver_str);

return (err);
}

/**
* notfound_err - generic error message for commands not found
* @shell_data: data
*  Return: Error message
*/

char *notfound_err(runtime_data *shell_data)
{
int len;
char *err;
char *ver_str;

ver_str = _itoa(shell_data->counter);
len = str_len(shell_data->av[0]) + str_len(ver_str);
len += str_len(shell_data->args[0]) + 16;
err = malloc(sizeof(char) * (len + 1));
if (err == 0)
{
free(err);
free(ver_str);
return (NULL);
}
str_cpy(err, shell_data->av[0]);
str_cat(err, ": ");
str_cat(err, ver_str);
str_cat(err, ": ");
str_cat(err, shell_data->args[0]);
str_cat(err, ": not found\n");
str_cat(err, "\0");
free(ver_str);
return (err);
}

/**
* exit_err - generic error message for exit in get_exit
* @shell_data: data
*
* Return: Error message
*/

char *exit_err(runtime_data *shell_data)
{
int len;
char *err;
char *ver_str;

ver_str = _itoa(shell_data->counter);
len = str_len(shell_data->av[0]) + str_len(ver_str);
len += str_len(shell_data->args[0]) + str_len(shell_data->args[1]) + 23;
err = malloc(sizeof(char) * (len + 1));
if (err == 0)
{
free(ver_str);
return (NULL);
}
str_cpy(err, shell_data->av[0]);
str_cat(err, ": ");
str_cat(err, ver_str);
str_cat(err, ": ");
str_cat(err, shell_data->args[0]);
str_cat(err, ": Illegal number: ");
str_cat(err, shell_data->args[1]);
str_cat(err, "\n\0");
free(ver_str);

return (err);
}
