#include "mini.h"
//TODO nothing's functionality is not tested in thes file
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

//line = smole lines in between pipes 
//index = index of the which in between pipe text it is
void set_rediractions(t_general *g_data, char *line, int index)
{
	int		temp_start_index;
	int		i;
	int		flag;
	char	*pathname;

	flag = 1;
	i = 0;
	temp_start_index = 0;
    while (line[i] != '\0')
	{
		if(line[i + 1] == '>')
		{
			i++;
			flag = 0;
			//TODO chch and change the flag accoring to > < >> << form man open 
			//TODO add check for redirection validity
			if (line[i + 1] == '>') 
			{
				flag = HEREDOC;
				i++;
			}
			if (!ft_strchr(METACHARACTERS, line[i]))
				temp_start_index = i;
			while (line[i] != '\0' && !ft_strchr(METACHARACTERS, line[i]))
			{
				i++;
			}
			if (temp_start_index != 0)
			{
				pathname = ft_substr(line, temp_start_index, i - temp_start_index);
				//TODO how check that this is the firs redirec head item ? 
				if (g_data->pipes[index].head_red == NULL)
					g_data->pipes[index].head_red = lst_redir_new(pathname, flag);
				else
					lst_redir_add_back(&g_data->pipes[index].head_red, lst_redir_new(pathname, flag));
			}
		}
		i++;
    }
}

void    paresing(t_general *g_data)
{
	int	i;

	i = 0;
	while (g_data->parse_data->pipes[i])
	{
		g_data->pipes[i].fd_in = 0;
		g_data->pipes[i].fd_out = 1;
		g_data->pipes[i].head_red = NULL;
	//	g_data->pipes[i]->argv = NULL; // TODO--------------------- what should go here? 
		set_rediractions(g_data, g_data->parse_data->pipes[i], i);
		i++;
	}
}
