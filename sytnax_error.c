#include "main.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int repeated_char(char *input, int i)
{
if (*(input - 1) == *input)
return (repeated_char(input - 1, i + 1));

return (i);
}

/**
 * error_separator - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_separator(char *input, int i, char last)
{
int count;

count = 0;
if (*input == '\0')
return (0);
if (*input == ' ' || *input == '\t')
return (error_separator(input + 1, i + 1, last));

if (*input == ';')
if (last == '|' || last == '&' || last == ';')
return (i);

if (*input == '|')
{
if (last == ';' || last == '&')
return (i);
if (last == '|')
{
count = repeated_char(input, 0);
if (count == 0 || count > 1)
return (i);
}
}

if (*input == '&')
{
if (last == ';' || last == '|')
return (i);

if (last == '&')
{
count = repeated_char(input, 0);
if (count == 0 || count > 1)
return (i);
}
}

return (error_separator(input + 1, i + 1, *input));
}

/**
 * first_char - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *input, int *i)
{
for (*i = 0; input[*i]; *i += 1)
{
if (input[*i] == ' ' || input[*i] == '\t')
continue;

if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
return (-1);

break;
}
return (0);
}

/**
 * print_error - prints when a syntax error is found
 *
 * @shell_data: data structure
 * @input: input string
 * @i: index of the error
 * @msg_err: to control msg error
 * Return: no return
 */
void print_error(runtime_data *shell_data, char *input, int i, int msg_err)
{
char *msg, *msg2, *msg3, *error, *counter;
int len;

if (input[i] == ';')
{
if (msg_err == 0)
msg = (input[i + 1] == ';' ? ";;" : ";");
else
msg = (input[i - 1] == ';' ? ";;" : ";");
}

if (input[i] == '|')
msg = (input[i + 1] == '|' ? "||" : "|");

if (input[i] == '&')
msg = (input[i + 1] == '&' ? "&&" : "&");
msg2 = ": Syntax error: \"";
msg3 = "\" unexpected\n";
counter = _itoa(shell_data->counter);
len = str_len(shell_data->av[0]) + str_len(counter);
len += str_len(msg) + str_len(msg2) + str_len(msg3) + 2;

error = malloc(sizeof(char) * (len + 1));
if (error == 0)
{
free(counter);
return;
}
str_cpy(error, shell_data->av[0]);
str_cat(error, ": ");
str_cat(error, counter);
str_cat(error, msg2);
str_cat(error, msg);
str_cat(error, msg3);
str_cat(error, "\0");
write(STDERR_FILENO, error, len);
free(error);
free(counter);
}

/**
 * check_error - intermediate function to
 * find and print a syntax error
 *
 * @shell_data: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_error(runtime_data *shell_data, char *input)
{
int begin = 0;
int f_char = 0;
int i = 0;

f_char = first_char(input, &begin);
if (f_char == -1)
{
print_error(shell_data, input, begin, 0);
return (1);
}
i = error_separator(input + begin, 0, *(input + begin));
if (i != 0)
{
print_error(shell_data, input, begin + i, 1);
return (1);
}
return (0);
}
