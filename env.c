#include "main.h"

/**
* set_env - adds an environment variable.
* @name:var name.
* @val:var value.
* Return:0 otherwise -1.
*/
int set_env(char *name, char *val)
{
int i = 0;
size_t len;
char *new;
len = str_len(name);
i = 0;
while (environ[i])
{
if (strncmp(environ[i], name, len) == 0)
{
new = var_build(name, val);
environ[i] = NULL;
environ[i] = str_dup(new);
free(environ[i]);
environ[i] = str_dup(new);
free(new);
return (0);
}
i++;
}
new = var_build(name, val);
free(environ[i]);
environ[i] = str_dup(new);
i++;
environ[i] = NULL;
new = NULL;

return (0);
}
/**
* var_build - Builds an environment variable
* @name: Var name.
* @val: Var value.
* Return: full environment variable.
*/
char *var_build(char *name, char *val)
{
char *new_variable;
size_t length;

length = str_len(name) + str_len(val) + 2;
new_variable = malloc(sizeof(char) * length);
if (new_variable == NULL)
{
perror("Error: Insufficient memory\n");
return (NULL);
}
memset(new_variable, 0, length);
new_variable = str_cat(new_variable, name);
new_variable = str_cat(new_variable, "=");
new_variable = str_cat(new_variable, val);

return (new_variable);
}
/**
* unset_env - Removes an environment variable.
* @name: Variable name.
* Return: 0 -1,otherwise -1.
*/
int unset_env(char *name)
{
int i = 0, j;
size_t length = strlen(name);
while (environ[i])
{
if (strncmp(environ[i], name, length) == 0)
{
free(environ[i]);
for (j = i; environ[j]; j++)
{
environ[j] = environ[j + 1];
}
}
else
{
i++;
}
}
return (0);
}
