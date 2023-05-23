#include "main.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void check_env(vars_list **h, char *in, runtime_data *data)
{
int row, chr, j, val;
char **envr;

envr = data->_environ;
for (row = 0; envr[row]; row++)
{
for (j = 1, chr = 0; envr[row][chr]; chr++)
{
if (envr[row][chr] == '=')
{
val = str_len(envr[row] + chr + 1);
add_var(h, j, envr[row] + chr + 1, val);
return;
}
if (in[j] == envr[row][chr])
j++;
else
break;
}
}
for (j = 0; in[j]; j++)
{
if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
break;
}
add_var(h, j, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(vars_list **h, char *in, char *st, runtime_data *data)
{
int i, lpd, lst;

lst = str_len(st);
lpd = str_len(data->pid);
for (i = 0; in[i]; i++)
{
if (in[i] == '$')
{
if (in[i + 1] == '?')
add_var(h, 2, st, lst), i++;
else if (in[i + 1] == '$')
add_var(h, 2, data->pid, lpd), i++;
else if (in[i + 1] == '\n')
add_var(h, 0, NULL, 0);
else if (in[i + 1] == '\0')
add_var(h, 0, NULL, 0);
else if (in[i + 1] == ' ')
add_var(h, 0, NULL, 0);
else if (in[i + 1] == '\t')
add_var(h, 0, NULL, 0);
else if (in[i + 1] == ';')
add_var(h, 0, NULL, 0);
else
check_env(h, in + i, data);
}
}
return (i);
}

/**
 * rep_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @new_len: new length
 * Return: replaced string
 */
char *rep_input(vars_list **head, char *input, char *new_input, int new_len)
{
vars_list *index;
int i, j, k;
index = *head;

for (j = i = 0; i < new_len; i++)
{
if (input[j] == '$')
{
if (!(index->len_var) && !(index->len_val))
{
new_input[i] = input[j];
j++;
}
else if (index->len_var && !(index->len_val))
{
for (k = 0; k < index->len_var; k++)
j++;
i--;
}
else
{
for (k = 0; k < index->len_val; k++)
{
new_input[i] = index->val[k];
i++;
}
j += (index->len_var);
i--;
}
index = index->next;
}
else
{
new_input[i] = input[j];
j++;
}
}
return (new_input);
}

/**
 * replace_var - calls functions to replace string into vars
 *
 * @input: input string
 * @shell_data: data structure
 * Return: replaced string
 */
char *replace_var(char *input, runtime_data *shell_data)
{
vars_list *head, *index;
char *status, *new_input;
int len, new_len;

status = _itoa(shell_data->status);
head = NULL;
len = check_vars(&head, input, status, shell_data);
if (head == NULL)
{
free(status);
return (input);
}
index = head;
new_len = 0;
while (index != NULL)
{
new_len += (index->len_val - index->len_var);
index = index->next;
}
new_len += len;
new_input = malloc(sizeof(char) * (new_len + 1));
new_input[new_len] = '\0';
new_input = rep_input(&head, input, new_input, new_len);
free(input);
free(status);
free_var(&head);
return (new_input);
}
