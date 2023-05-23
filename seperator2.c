#include "main.h"

/**
 * add_var - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @var_len: length of the variable.
 * @val: value of the variable.
 * @val_len: length of the value.
 * Return: address of the head.
 */
vars_list *add_var(vars_list **head, int var_len, char *val, int val_len)
{
vars_list *new, *temp;

new = malloc(sizeof(vars_list));
if (new == NULL)
return (NULL);
new->len_var = var_len;
new->val = val;
new->len_val = val_len;
new->next = NULL;
temp = *head;
if (temp == NULL)
{
*head = new;
}
else
{
while (temp->next != NULL)
temp = temp->next;
temp->next = new;
}

return (*head);
}

/**
 * free_var - frees a r_var list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_var(vars_list **head)
{
vars_list *temp;
vars_list *current;

if (head != NULL)
{
current = *head;
while ((temp = current) != NULL)
{
current = current->next;
free(temp);
}
*head = NULL;
}
}
