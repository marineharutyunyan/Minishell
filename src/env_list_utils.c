/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lohanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:37:54 by lohanyan          #+#    #+#             */
/*   Updated: 2023/03/16 16:40:51 by lohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini.h"

t_env	*lst_env_last(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	del_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	del_all_env(t_general *g_data)
{
	t_env	*prev;
	t_env	*temp;

	temp = g_data->head_env;
	prev = NULL;
	while (temp)
	{
		prev = temp;
		temp = temp->next;
		del_node(prev);
	}
	g_data->head_env = NULL;
}

int	find_and_replace_node(t_env *lst, t_env *new)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, new->key) == 0)
		{
			if (ft_strcmp(lst->value, new->value) != 0)
			{
				free(lst->value);
				lst->value = ft_strdup(new->value);
			}
			del_node(new);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void	lst_env_add(t_env **lst, t_env *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (find_and_replace_node(*lst, new) == 0)
	{
		lst_env_last(*lst)->next = new;
	}
}

/*void	lst_env_add_back(t_env **lst, t_env *new)
{	
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
}*/

t_env	*lst_env_new(void *key, void *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node)
	{
		node->key = ft_strdup(key);
		node->value = ft_strdup(value);
		node->next = NULL;
		return (node);
	}
	return (NULL);
}
