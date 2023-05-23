#include "main.h"

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
int count = 0, i, j;
char *string, temp;

while (count >= 0)
{
if (s[count] == '\0')
break;
count++;
}
string = s;

for (i = 0; i < (count - 1); i++)
{
for (j = i + 1; j > 0; j--)
{
temp = *(string + j);
*(string + j) = *(string + (j - 1));
*(string + (j - 1)) = temp;
}
}
}
