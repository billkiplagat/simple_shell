#include "main.h"



/**
 * str_len - Returns length of a string.
 * @s: Pointer to string.
 * Return: Length of s.
 */
int str_len(char *s)
{
int ind;

ind = 0;
while (s[ind] != '\0')
{
ind++;
}
return (ind);
}

/**
 * str_tok - Mimics strtok, which tokenizes a string and turn to array.
 * @src: String from getline.
 * @delim: " ";
 * Return: Individual token in array format.
 */

char *str_tok(char *src, const char *delim)
{
static char *s;
static unsigned int i;
char *res = NULL;
int space = 0;

if (src)
{
s = src;
for (i = 0; s[i]; i++)
{
if (is_delimiter(s[i], delim))
s[i] = '\0';
}
}
if (s == NULL || *s == '\0')
return (NULL);
res = s;
i = str_len(s);
if (s[i] == '\0' && str_len(s) > 0)
space = 1;
s = s + str_len(s) + space;
return (res);
}


/**
 * str_cpy - Copies the string pointed to by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest.
 * @dest: Copy source to this buffer.
 * @src: This is the source to copy.
 * Return: Copy of original source.
 */

char *str_cpy(char *dest, char *src)
{
int i, length;

for (length = 0; src[length] != '\0'; length++)
;
for (i = 0; i <= length; i++)
dest[i] = src[i];

return (dest);
}

/**
 * get_line - Stores into malloced buffer the user's command into shell.
 * @str: Buffer.
 * Return: Number of characters read.
 */
ssize_t get_line(char **str)
{
ssize_t i = 0, s = 0, l = 0, t2 = 0, n = 0;
char buffer[1024];

while (t2 == 0 && (i = read(STDIN_FILENO, buffer, 1024 - 1)))
{
if (i == -1)
return (-1);
buffer[i] = '\0';
n = 0;
while (buffer[n] != '\0')
{
if (buffer[n] == '\n')
t2 = 1;
n++;
}
if (l == 0)
{
i++;
*str = malloc(sizeof(char) * i);
*str = str_cpy(*str, buffer);
s = i;
l = 1;
}
else
{
s += i;
*str = str_cat(*str, buffer);
}
}
return (s);
}
/**
 *  str_dup - Duplicates string.
 *  @str: String to duplicate.
 *  Return: Pointer to duplicated string in allocated memory.
 */
char *str_dup(char *str)
{
char *dup_string;
int i, len = 0;

if (str == NULL)
return (NULL);
while (str[len])
len++;
len++;
dup_string = malloc(sizeof(char) * len);
if (dup_string == NULL)
return (NULL);
i = 0;
while (i < len)
{
dup_string[i] = str[i];
i++;
}
return (dup_string);
}
