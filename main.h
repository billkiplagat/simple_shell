#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>


extern char **environ;
int set_env(char *var_name, char *var_value);
int unset_env(char *var_name);
char *str_dup(char *str);
void _puts(char *str);
void prompt(void);
int change_dir(char **argv);
char *readLine(void);
int str_len(char *s);
char *str_cat(char *dest, char *src);
int _putchar(char c);
int str_cmp(char *s1, char *s2);
char **string_to_token(char *str);
unsigned int check_white_space(char *s);
int exe_func(char **tokens, char *args);
void print_env(void);
char *str_tok(char *src, const char *delim);
char *str_cpy(char *dest, char *src);
ssize_t get_line(char **str);
int handle_path(char **tokens);
int file_exits(char *s);
void _kill(char *lineptr, char *tmp, char **tok);
void exit_shell(char **tokens, char *line);
void ctr_lc(int signum);
int is_delimiter(char c, const char *delim);
int exec_builtin(char **tokens);
int _builtins(char *str);
int _atoi(char *s);
char *path_builder(char **tokens);
int execute2(char **tokens, char *path, char *args);
char *var_build(char *var_name, char *var_value);


#endif
