#include "mini.h"

/*int	ft_lstsize(t_red *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		++i;
	}
	return (i);
}*/

void	ft_redir_iter(t_red *lst)
{
	while (lst)
	{
		printf("Pathname = %s\n", lst->pathname);
		printf("flage = %d\n", lst->flag);
		lst = lst->next;
	}
}
