#include "main.h"

/**
 * swap_chars - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_chars(char *input, int bool)
{
int i;

if (bool == 0)
{
for (i = 0; input[i]; i++)
{
if (input[i] == '|')
{
if (input[i + 1] != '|')
input[i] = 16;
else
i++;
}
if (input[i] == '&')
{
if (input[i + 1] != '&')
input[i] = 12;
else
i++;
}
}
}
else
{
for (i = 0; input[i]; i++)
{
input[i] = (input[i] == 16 ? '|' : input[i]);
input[i] = (input[i] == 12 ? '&' : input[i]);
}
}
return (input);
}

/**
 * add_node - add separators and command lines in the lists
 *
 * @s_head: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void add_node(sep_list **s_head, line_list **head_l, char *input)
{
char *line;
int i;

input = swap_chars(input, 0);
for (i = 0; input[i]; i++)
{
if (input[i] == ';')
add_separator(s_head, input[i]);

if (input[i] == '|' || input[i] == '&')
{
add_separator(s_head, input[i]);
i++;
}
}
line = str_tok(input, ";|&");
do {
line = swap_chars(line, 1);
add_line_node(head_l, line);
line = str_tok(NULL, ";|&");
} while (line != NULL);
}

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @shell_data: data structure
 * Return: no return
 */
void go_next(sep_list **list_s, line_list **list_l, runtime_data *shell_data)
{
int loop_sep;
sep_list *ls_s;
line_list *ls_l;

loop_sep = 1;
ls_s = *list_s;
ls_l = *list_l;
while (ls_s != NULL && loop_sep)
{
if (shell_data->status == 0)
{
if (ls_s->separator == '&' || ls_s->separator == ';')
loop_sep = 0;
if (ls_s->separator == '|')
ls_l = ls_l->next, ls_s = ls_s->next;
}
else
{
if (ls_s->separator == '|' || ls_s->separator == ';')
loop_sep = 0;
if (ls_s->separator == '&')
ls_l = ls_l->next, ls_s = ls_s->next;
}
if (ls_s != NULL && !loop_sep)
ls_s = ls_s->next;
}
*list_s = ls_s;
*list_l = ls_l;
}
/**
 * split_command - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @shell_data: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split_command(runtime_data *shell_data, char *input)
{
sep_list *s_head, *list_s;
line_list *head_l, *list_l;
int loop;

s_head = NULL;
head_l = NULL;
add_node(&s_head, &head_l, input);
list_s = s_head;
list_l = head_l;
while (list_l != NULL)
{
shell_data->input = list_l->line;
shell_data->args = splitLine(shell_data->input);
loop = execute_line(shell_data);
free(shell_data->args);
if (loop == 0)
break;
go_next(&list_s, &list_l, shell_data);
if (list_l != NULL)
list_l = list_l->next;
}
free_separator(&s_head);
free_line(&head_l);
if (loop == 0)
return (0);
return (1);
}

/**
 * splitLine - tokenizes the input string
 *
 * @input: input string.
 * Return: split string.
 */
char **splitLine(char *input)
{
char **tokens;
char *token;
size_t l_size;
size_t i;

l_size = SEC_BUFFER;
tokens = malloc(sizeof(char *) * (l_size));
if (tokens == NULL)
{
write(STDERR_FILENO, ": Allocation Error\n", 18);
exit(EXIT_FAILURE);
}
token = str_tok(input, TOK_DELIM);
tokens[0] = token;
for (i = 1; token != NULL; i++)
{
if (i == l_size)
{
l_size += SEC_BUFFER;
tokens = realloc_dp(tokens, i, sizeof(char *) * l_size);
if (tokens == NULL)
{
write(STDERR_FILENO, ": Allocation Error\n", 18);
exit(EXIT_FAILURE);
}
}
token = str_tok(NULL, TOK_DELIM);
tokens[i] = token;
}
return (tokens);
}
