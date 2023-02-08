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
