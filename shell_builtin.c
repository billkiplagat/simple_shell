#include "main.h"

/**
 * built_in - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*built_in(char *cmd))(runtime_data *)
{
builtin_t builtin[] = {
{ "env", _env },
{ "exit", exit_shell },
{ "setenv", _setenv },
{ "unsetenv", _unsetenv },
{ "cd", cd_shell },
{ "help", get_help },
{ NULL, NULL }
};
int i;
for (i = 0; builtin[i].name; i++)
{
if (str_cmp(builtin[i].name, cmd) == 0)
break;
}
return (builtin[i].f);
}
