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

int pass_spces(char *line, int i)
{
	while (line[i] != '\0' && ft_strchr(SPACE, line[i]))
		i++;
	return (i);
}

int pass_quotes(char *str, int i)
{
	char c;

	if (str[i] == '\'' || str[i] == '"')
	{
		c = str[i];
		i++;
		while (str[i] != c  && str[i] != '\0')
		{
			i++;
		}
	}
	return (i);
}

char *get_word(char *line, int *i)
{
	int start_index = *i;
	
	while (line[*i] != '\0' && !ft_strchr(METACHARACTERS, line[*i]))
	{
		*i = pass_quotes(line, *i);
		(*i)++;
	}
	return (ft_substr(line, start_index, (*i) - start_index));
}

//line = smole lines in between pipes 
//index = index of the which in between pipe text it is

// TODO Fix and free for multiple time command submition the last element arent being cleanwed 
void set_args(t_general *g_data, char *line, int index)
{
	int	i;
	int j;

	g_data->pipes[index].argv = malloc(sizeof (char *) * (g_data->pipes[index].words_count + 1));
	g_data->pipes[index].argv[g_data->pipes[index].words_count] = NULL;
	i = 0;
	j = 0;
    while (line[i] != '\0')
	{
		i = pass_spces(line, i);		
		if (ft_strchr(REDIRECTIONS, line[i]))
		{
			while (ft_strchr(REDIRECTIONS, line[i]))
			{
				i++;
			}
			i = pass_spces(line, i);
			free(get_word(line, &i));
		}
		else if (line[i] != '\0')
		{
			//printf("it's an agrument%d\n", i);
			i = pass_spces(line, i);
			g_data->pipes[index].argv[j] = get_word(line, &i);
			j++;
		}
	}
}
// dhgsdfhs >> dfgsd > fhgfgh   |
//line = smole lines in between pipes 
//index = index of the which in between pipe text it is
void set_rediractions(t_general *g_data, char *line, int index)
{
	int		temp_start_index;
	int		i;
	int		flag;

	flag = 1;
	i = -1;
	temp_start_index = 0;
    while (line[++i] != '\0')
	{
		i = pass_spces(line, i);
		flag = 9; //some random false flag value 
		// TODO norminet 
		if (line[i] == '>' && line[i + 1] == '>') 
		{
			flag = O_APPEND; // opening file and seting index  of cursor at very end of file.
			i = i + 2;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			flag = HEREDOC; // opening virtual file and letting write command and maybe u can pass that file as an input to some pipe.
			i = i + 2;
		}
		else if (line[i] == '>')
		{
			flag = O_TRUNC; // opening file and deleting everything in it.
			i++;
		}
		else if (line[i] == '<') 
		{
			flag = O_RDONLY; // opening file and only reading 
			i++;
		}
		else if (line[i] != '\0')
		{
			i = pass_spces(line, i);
			g_data->pipes[index].words_count += 1;
			get_word(line, &i);
		}
		//TODO add check for redirection validity
		if (flag != 9)
		{
			i = pass_spces(line, i);
			if (g_data->pipes[index].head_red == NULL)
				g_data->pipes[index].head_red = lst_redir_new(get_word(line, &i), flag);
			else
				lst_redir_add_back(&g_data->pipes[index].head_red, lst_redir_new(get_word(line, &i), flag));
		}
    }
}

void    paresing(t_general *g_data)
{
	int	i;

	i = 0;
	while (g_data->parse_data.pipes[i])
	{
		g_data->pipes[i].fd_in = 0;
		g_data->pipes[i].fd_out = 1;
		g_data->pipes[i].head_red = NULL;
		g_data->pipes[i].words_count = 0;
		g_data->pipes[i].argv = NULL;
		
		// TODO--------------------- what should go here? 
		set_rediractions(g_data, g_data->parse_data.pipes[i], i);
		set_args(g_data, g_data->parse_data.pipes[i], i);
		int j;

		j = 0;
		while (g_data->pipes[i].argv[j])
		{
			printf("argv = %s\n", g_data->pipes[i].argv[j]);
			j++;
		}
		
		//printf("argv = %d\n", g_data->pipes[i].words_count);
		// for printing 
		//ft_redir_iter(g_data->pipes[i].head_red);
		i++;
	}
}
