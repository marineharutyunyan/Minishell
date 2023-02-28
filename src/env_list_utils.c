#include "mini.h"

t_env	*lst_env_last(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_env_add_back(t_env **lst, t_env *new)
{	
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lst_env_last(*lst)->next = new;
}

t_env	*lst_env_new(void *key, void *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node)
	{	
		node->key = key;
		node->value = value;
		node->next = NULL;
		return (node);
	}
	else
	{
		return (NULL);
	}
}

void	lst_env_delet_by_key(t_env *lst, char	*key)
{
/*
// Store head node
	t_env *prev;
	t_env *temp = *lst;

	// If head node itself holds the key to be deleted
	if (temp != NULL && temp->key == key) {
		*lst = *(temp->next); // Changed head
		free(temp); // free old head
		return ;
	}
	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (temp != NULL && temp->key != key) {
		prev = temp;
		temp = temp->next;
	}
	// If key was not present in linked list
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);*/
}
