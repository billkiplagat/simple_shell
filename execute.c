#include "main.h"

/**
* exe_func - Executes a file.
* @token: Split string into token
* @args: Program arguments.
* Return: 0 otherwise - 1.
*/
int exe_func(char **token, char *args)
{
char *error, *error2, *error3;
pid_t pid;
int status;
char *path;
if (_builtins(*token) == 0)
{
status = exec_builtin(token);
return (status);
}
path = path_builder(token);
if (path != NULL)
{
status = execute2(token, path, args);
return (status);
}
pid = fork();
if (pid == -1)
{
perror("Error: ");
return (1);
}
if (pid == 0)
{
if (execve(token[0], token, NULL) == -1)
{
error = str_cat(*token, ": No such file or directory\n");
error2 = str_cat(args, ":");
error3 = str_cat(error2, error);
write(STDERR_FILENO, error3, str_len(error3));
free(token);
exit(EXIT_FAILURE);
}
return (EXIT_SUCCESS);
}
wait(&status);
return (0);
}

