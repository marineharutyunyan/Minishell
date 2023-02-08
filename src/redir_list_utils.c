#include "mini.h"

t_red	*lst_redir_last(t_red *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_redir_add_back(t_red **lst, t_red *new)
{	
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lst_redir_last(*lst)->next = new;
}

t_red	*lst_redir_new(void *content, int flag_num)
{
	t_red	*node;

	node = (t_red *)malloc(sizeof(t_red));
	if (node)
	{	
		node->flag = flag_num;
		node->pathname = content;
		node->next = NULL;
		return (node);
	}
	else
	{
		return (NULL);
	}
}