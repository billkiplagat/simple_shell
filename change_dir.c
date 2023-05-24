#include "main.h"
#define PATH_MAX 4096

/**
 * change_dir - changes the current directory
 * @argv: array of string
 * Return: 1 for success else fail
 */


int change_dir(char **argv)
{
	char *dir, cwd[PATH_MAX];

	if (argv[1] == NULL)
	{
		dir = getenv("HOME");
		if (dir == NULL)
		{
			perror("getenv");
			return (1);
		}
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		dir = getenv("OLDPWD");
		if (dir == NULL)
		{
			perror("getenv");
			return (1);
		}
	}
	else
		dir = argv[1];
	if (chdir(dir) != 0)
	{
		perror("chdir");
		return (1);
	}
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	} else
	{
		perror("Can't get previous dir");
		return (1);
	}
	return (0);
}
