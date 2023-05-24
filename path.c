#include "main.h"


/**
 * path_builder - Constructs a path to binaries.
 * @tokens: Double pointer to tokens.
 * Return: Return - path, else - NULL.
 */
char *path_builder(char **tokens)
{
char path[100] = "/bin/";
char path2[100] = "/usr/bin/";

char *final_path;
char *final_path2;
final_path = str_cat(path, tokens[0]);
if ((file_exits(final_path) == 0))
return (final_path);

final_path2 = str_cat(path2, tokens[0]);
if ((file_exits(final_path2) == 0))
return (final_path2);
return (NULL);
}
/**
 * file_exits - Checks file status.
 * @s: Pointer to file name.
 * Return: 0 if success, else non zero.
 */
int file_exits(char *s)
{
struct stat st;
return (stat(s, &st));
}

/**
 * execute2 - Executes a file.
 * @tokens: Split string into tokens from stdin.
 * @path: Path from path_builder function.
 * @args: Program arguments.
 * Return: 0 - on success, else - 1.
 */
int execute2(char **tokens, char *path, char *args)
{
char *error, *error2, *error3;
pid_t pid;
int stat;

pid = fork();
if (pid == -1)
{
perror("Error: ");
return (1);
}
if (pid == 0)
{
tokens[0] = path;
if (execve(tokens[0], tokens, NULL) == -1)
{
error = str_cat(*tokens, ": No such file or directory\n");
error2 = str_cat(args, ":");
error3 = str_cat(error2, error);
write(STDERR_FILENO, error3, str_len(error3));
free(tokens);
exit(EXIT_FAILURE);
}
return (EXIT_SUCCESS);
}
wait(&stat);
return (EXIT_SUCCESS);
}
