#include "main.h"

/**
* cd_dot - changes to the parent directory
*
* @shell_data: data environ
*
* Return: no return
*/
void cd_dot(runtime_data *shell_data)
{
char pwd[PATH_MAX];
char *dir, *cd_pwd, *cp_str_tok_pwd;

getcwd(pwd, sizeof(pwd));
cd_pwd = str_dup(pwd);
set_env("OLDPWD", cd_pwd, shell_data);
dir = shell_data->args[1];
if (str_cmp(".", dir) == 0)
{
set_env("PWD", cd_pwd, shell_data);
free(cd_pwd);
return;
}
if (str_cmp("/", cd_pwd) == 0)
{
free(cd_pwd);
return;
}
cp_str_tok_pwd = cd_pwd;
rev_string(cp_str_tok_pwd);
cp_str_tok_pwd = str_tok(cp_str_tok_pwd, "/");
if (cp_str_tok_pwd != NULL)
{
cp_str_tok_pwd = str_tok(NULL, "\0");

if (cp_str_tok_pwd != NULL)
rev_string(cp_str_tok_pwd);
}
if (cp_str_tok_pwd != NULL)
{
chdir(cp_str_tok_pwd);
set_env("PWD", cp_str_tok_pwd, shell_data);
}
else
{
chdir("/");
set_env("PWD", "/", shell_data);
}
shell_data->status = 0;
free(cd_pwd);
}

/**
* cd_to - changes to a directory given
*
* @shell_data: data relevant
* Return: no return
*/
void cd_to(runtime_data *shell_data)
{
char pwd[PATH_MAX];
char *dir, *cd_pwd, *cp_dir;

getcwd(pwd, sizeof(pwd));

dir = shell_data->args[1];
if (chdir(dir) == -1)
{
get_error(shell_data, 2);
return;
}
cd_pwd = str_dup(pwd);
set_env("OLDPWD", cd_pwd, shell_data);

cp_dir = str_dup(dir);
set_env("PWD", cp_dir, shell_data);
free(cd_pwd);
free(cp_dir);
shell_data->status = 0;
chdir(dir);
}

/**
* cd_previous - changes to the previous directory
*
* @shell_data: data relevant
* Return: no return
*/
void cd_previous(runtime_data *shell_data)
{
char pwd[PATH_MAX];
char *p_pwd, *p_oldpwd, *cd_pwd, *cp_oldpwd;

getcwd(pwd, sizeof(pwd));
cd_pwd = str_dup(pwd);

p_oldpwd = _getenv("OLDPWD", shell_data->_environ);

if (p_oldpwd == NULL)
cp_oldpwd = cd_pwd;
else
cp_oldpwd = str_dup(p_oldpwd);

set_env("OLDPWD", cd_pwd, shell_data);

if (chdir(cp_oldpwd) == -1)
set_env("PWD", cd_pwd, shell_data);
else
set_env("PWD", cp_oldpwd, shell_data);

p_pwd = _getenv("PWD", shell_data->_environ);

write(STDOUT_FILENO, p_pwd, str_len(p_pwd));
write(STDOUT_FILENO, "\n", 1);

free(cd_pwd);
if (p_oldpwd)
free(cp_oldpwd);

shell_data->status = 0;

chdir(p_pwd);
}

/**
* cd_to_home - changes to home directory
*
* @shell_data: data relevant (environ)
* Return: no return
*/
void cd_to_home(runtime_data *shell_data)
{
char *p_pwd, *home;
char pwd[PATH_MAX];

getcwd(pwd, sizeof(pwd));
p_pwd = str_dup(pwd);

home = _getenv("HOME", shell_data->_environ);

if (home == NULL)
{
set_env("OLDPWD", p_pwd, shell_data);
free(p_pwd);
return;
}

if (chdir(home) == -1)
{
get_error(shell_data, 2);
free(p_pwd);
return;
}

set_env("OLDPWD", p_pwd, shell_data);
set_env("PWD", home, shell_data);
free(p_pwd);
shell_data->status = 0;
}
#include "main.h"

/**
* cd_shell - changes current directory
*
* @shell_data: data relevant
* Return: 1 on success
*/
int cd_shell(runtime_data *shell_data)
{
char *dir;
int home, home2, is_dash;
dir = shell_data->args[1];
if (dir != NULL)
{
home = str_cmp("$HOME", dir);
home2 = str_cmp("~", dir);
is_dash = str_cmp("--", dir);
}
if (dir == NULL || !home || !home2 || !is_dash)
{
cd_to_home(shell_data);
return (1);
}
if (str_cmp("-", dir) == 0)
{
cd_previous(shell_data);
return (1);
}
if (str_cmp(".", dir) == 0 || str_cmp("..", dir) == 0)
{
cd_dot(shell_data);
return (1);
}
cd_to(shell_data);
return (1);
}
