#include "main.h"

/**
 * prompt - Print prompt.
 * Return: Void.
 */
void prompt(void)
{
	char *prmpt = "$ ";
if (isatty(STDIN_FILENO))
{
write(STDOUT_FILENO, prmpt, strlen(prmpt));
}
}
