#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#define MAIN_BUFFER 1024
#define SEC_BUFFER 128
#define TOK_DELIM " \t\r\n\a"
/* Points to an array of pointers to strings */
extern char **environ;
/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
    char **av;
    char *input;
    char **args;
    int status;
    int counter;
    char **_environ;
    char *pid;
} runtime_data;
/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
    char *line;
    struct line_list_s *next;
} line_list;
/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
    char separator;
    struct sep_list_s *next;
} sep_list;
/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
    int len_var;
    char *val;
    int len_val;
    struct r_var_list *next;
} vars_list;
/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
    char *name;
    int (*f)(runtime_data *data);
} builtin_t;

/* separator.c */
sep_list *add_separator(sep_list **head, char sep);
void free_separator(sep_list **head);
line_list *add_line_node(line_list **head, char *line);
void free_line(line_list **head);

/* separator2.c */
vars_list *add_var(vars_list **head, int lvar, char *var, int lval);
void free_var(vars_list **head);

/* shell_str */
char *str_cat(char *dest, const char *src);
char *str_cpy(char *dest, char *src);
int str_cmp(char *s1, char *s2);
char *str_chr(char *s, char c);
int str_spn(char *s, char *accept);

/* shell_mem.c */
void mem_cpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **realloc_dp(char **ptr, unsigned int old_size, unsigned int new_size);

/* shell_str2.c */
char *str_dup(const char *s);
int str_len(const char *s);
int cmp_chars(char str[], const char *delim);
char *str_tok(char str[], const char *delim);
int is_digit(const char *s);

/* shell_str3.c */
void rev_string(char *s);

/* syntax_error.c */
int repeated_char(char *input, int i);
int error_separator(char *input, int i, char last);
int first_char(char *input, int *i);
void print_error(runtime_data *data, char *input, int i, int bool);
int check_error(runtime_data *data, char *input);

/* loop.c */
char *comment(char *in);
void loop(runtime_data *data);

/* read_line.c */
char *readLine(int *i_eof);

/* split.c */
char *swap_chars(char *input, int bool);
void add_node(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, runtime_data *data);
int split_command(runtime_data *data, char *input);
char **splitLine(char *input);

/* variables.c */
void check_env(vars_list **h, char *in, runtime_data *data);
int check_vars(vars_list **h, char *in, char *st, runtime_data *data);
char *rep_input(vars_list **head, char *input, char *new_input, int nlen);
char *replace_var(char *input, runtime_data *data);

/* shell_line.c */
void bringLine(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* execute_line.c */
int execute_line(runtime_data *data);

/* exec_cmd.c */
int _cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int executable(runtime_data *data);
int check_cmd_err(char *dir, runtime_data *data);
int execute_cmd(runtime_data *data);

/* env.c */
int cmp_env_name(const char *env_name, const char *name);
char *_getenv(const char *name, char **_environ);
int _env(runtime_data *data);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, runtime_data *data);
int _setenv(runtime_data *data);
int _unsetenv(runtime_data *data);

/* cd.c */
void cd_previous(runtime_data *data);
void cd_to_home(runtime_data *data);
void cd_dot(runtime_data *data);
void cd_to(runtime_data *data);
int cd_shell(runtime_data *data);

/* shell_builtin.c */
int (*built_in(char *cmd))(runtime_data *data);

/* exit_shell.c */
int exit_shell(runtime_data *data);

/* aux_stdlib.c */
int get_len(int n);
char *_itoa(int n);
int _atoi(char *s);

/* errors.c */
char *str_cat_cd(runtime_data *, char *, char *, char *);
char *get_cd_err(runtime_data *data);
char *notfound_err(runtime_data *data);
char *exit_err(runtime_data *data);

/* errors2.c */
char *env_err(runtime_data *data);
char *path_err(runtime_data *data);


/* get_error.c */
int get_error(runtime_data *data, int eval);

/* shell_sigint.c */
void get_sigint(int sig);

/* help.c */
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_general(void);
void help_exit(void);

/* help2.c */
void builtin_help(void);
void alias_help(void);
void cd_help(void);

/* get_help.c */
int get_help(runtime_data *data);

#endif
