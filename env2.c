#include "main.h"

/**
* copy_info - copies info to create
* a new env or alias
* @name: name env or alias
* @value: value env or alias
*
* Return: new env or alias.
*/
char *copy_info(char *name, char *value)
{
char *new;
int name_len, len_value, len;

name_len = str_len(name);
len_value = str_len(value);
len = name_len + len_value + 2;
new = malloc(sizeof(char) * (len));
str_cpy(new, name);
str_cat(new, "=");
str_cat(new, value);
str_cat(new, "\0");

return (new);
}

/**
* set_env - sets an environment variable
*
* @name: name of the environment
* @value: value of the environment
* @shell_data: data
* Return: no return
*/
void set_env(char *name, char *value, runtime_data *shell_data)
{
int i;
char *env_var, *env_name;

for (i = 0; shell_data->_environ[i]; i++)
{
env_var = str_dup(shell_data->_environ[i]);
env_name = str_tok(env_var, "=");
if (str_cmp(env_name, name) == 0)
{
free(shell_data->_environ[i]);
shell_data->_environ[i] = copy_info(env_name, value);
free(env_var);
return;
}
free(env_var);
}

shell_data->_environ = realloc_dp(shell_data->_environ, i,
sizeof(char *) * (i + 2));
shell_data->_environ[i] = copy_info(name, value);
shell_data->_environ[i + 1] = NULL;
}

/**
* _setenv - compares env variables names
* with the name passed.
* @shell_data: env name and env value
*
* Return: 1 on success.
*/
int _setenv(runtime_data *shell_data)
{
if (shell_data->args[1] == NULL || shell_data->args[2] == NULL)
{
get_error(shell_data, -1);
return (-2);
}
set_env(shell_data->args[1], shell_data->args[2], shell_data);

return (1);
}

/**
* _unsetenv - deletes a environment variable
*
* @shell_data: data
*
* Return: 1 on success.
*/
int _unsetenv(runtime_data *shell_data)
{
int i, j, k;
char **realloc_environ;
char *env_var, *env_name;


if (shell_data->args[1] == NULL)
{
get_error(shell_data, -1);
return (-1);
}
k = -1;
for (i = 0; shell_data->_environ[i]; i++)
{
env_var = str_dup(shell_data->_environ[i]);
env_name = str_tok(env_var, "=");
if (str_cmp(env_name, shell_data->args[1]) == 0)
{
k = i;
}
free(env_var);
}
if (k == -1)
{
get_error(shell_data, -1);
return (-1);
}
realloc_environ = malloc(sizeof(char *) * (i));
for (i = j = 0; shell_data->_environ[i]; i++)
{
if (i != k)
{
realloc_environ[j] = shell_data->_environ[i];
j++;
}
}
realloc_environ[j] = NULL;
free(shell_data->_environ[k]);
free(shell_data->_environ);
shell_data->_environ = realloc_environ;
return (1);
}
