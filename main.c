#include "main.h"

/**
* free_data - frees data structure
*
* @shell_data: data structure
* Return: no return
*/
void free_data(runtime_data *shell_data)
{
unsigned int j;
for (j = 0; shell_data->_environ[j]; j++)
{
free(shell_data->_environ[j]);
}
free(shell_data->_environ);
free(shell_data->pid);
}
/**
* set_data - Initialize data structure
*
* @shell_data: data structure
* @av: argument vector
* Return: no return
*/
void set_data(runtime_data *shell_data, char **av)
{
unsigned int i;
shell_data->av = av;
shell_data->input = NULL;
shell_data->args = NULL;
shell_data->status = 0;
shell_data->counter = 1;
for (i = 0; environ[i]; i++)
shell_data->_environ = malloc(sizeof(char *) * (i + 1));
for (i = 0; environ[i]; i++)
{
shell_data->_environ[i] = str_dup(environ[i]);
}
shell_data->_environ[i] = NULL;
shell_data->pid = _itoa(getpid());
}

/**
* main - Entry point
*
* @ac: argument count
* @av: argument vector
*
* Return: 0 on success.
*/
int main(int ac, char **av)
{
runtime_data shell_data;
(void) ac;
signal(SIGINT, get_sigint);
set_data(&shell_data, av);
loop(&shell_data);
free_data(&shell_data);
if (shell_data.status < 0)
return (255);
return (shell_data.status);
}
