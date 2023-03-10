#include "mini.h"

//line = smole lines in between pipes
void	set_args(t_pipe *pipe, char *line)
{
	int		i;
	int		j;
	char	*word;

	if (pipe->words_count == 0)
		return ;
	pipe->argv = malloc(sizeof (char *) * (pipe->words_count + 1));
	pipe->argv[pipe->words_count] = NULL;
	i = 0;
	j = 0;
	word = NULL;
	while (line[i] != '\0')
	{
		i = pass_spces(line, i);
		i = pass_redir(line, i);
		word = get_word(line, &i);
		if (word != NULL)
			pipe->argv[j++] = word;
	}
}

int	get_redir_flag(char *line, int *i)
{
	int		flag;

	flag = 9; //some random false flag value 
	if (line[*i] == '>' && line[(*i) + 1] == '>')
	{
		flag = O_APPEND; // opening file and seting index  of cursor at very end of file.
		*i = (*i) + 2;
	}
	else if (line[*i] == '<' && line[(*i) + 1] == '<')
	{
		flag = HEREDOC; // opening virtual file and letting write command and maybe u can pass that file as an input to some pipe.
		*i = (*i) + 2;
	}
	else if (line[*i] == '>')
	{
		flag = O_TRUNC; // opening file and deleting everything in it.
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		flag = O_RDONLY; // opening file and only reading 
		(*i)++;
	}
	return (flag);
}

int replace_dollar_varables(t_general *g_data, int i)
{
	int 	j;
	t_red 	*temp;

	j = 0;
	while (g_data->pipes[i].argv[j])
	{
		g_data->pipes[i].argv[j] = process_dollar_sign_and_quotes(g_data->pipes[i].argv[j], g_data);
		j++;
	}
	temp = g_data->pipes[i].head_red;
	while (temp)
	{
		if (temp->flag != HEREDOC)
			temp->pathname = process_dollar_sign_and_quotes(temp->pathname, g_data);
		temp = temp->next;
	}
	return(0);
}
// dhgsdfhs >> dfgsd > fhgfgh   |
//line = smole lines in between pipes 
//index = index of the which in between pipe text it is
void	set_rediractions(t_pipe *pipe, char *line)
{
	int		temp_start_index;
	int		i;
	int		flag;
	char	*word;

	i = 0;
	temp_start_index = 0;
	while (line[i] != '\0')
	{
		i = pass_spces(line, i);
		flag = get_redir_flag(line, &i);
		if (flag == 9 && line[i] != '\0')
		{
			i = pass_spces(line, i);
			pipe->words_count += 1;
			free(get_word(line, &i));
		} //TODO add check for redirection validity
		if (flag != 9)
		{
			i = pass_spces(line, i);
			word = get_word(line, &i);
			if (pipe->head_red == NULL)
				pipe->head_red = lst_redir_new(word, flag);
			else
				lst_redir_add_back(&pipe->head_red, lst_redir_new(word, flag));
		}
		if (line[i])
			i++;
	}
}

// export a="barev"
// TODO error case     cat|ls pipe count isn't neing counted correctly -fix -segfault with sanitazer
int	parsing(t_general *g_data)
{
	int	i;
	int	j;

	i = 0;
	while (g_data->parse_data.pipes[i])
	{
		g_data->pipes[i].fd_in = 0;
		g_data->pipes[i].fd_out = 1;
		g_data->pipes[i].head_red = NULL;
		g_data->pipes[i].words_count = 0;
		g_data->pipes[i].argv = NULL;
		g_data->pipes[i].cmd_name = NULL;		set_rediractions(&g_data->pipes[i], g_data->parse_data.pipes[i]);
		set_args(&g_data->pipes[i], g_data->parse_data.pipes[i]);
		// for PRINTING
		/*
		j = 0;
		while (g_data->pipes[i].argv[j])
		{
			printf("argv = %s\n", g_data->pipes[i].argv[j]);
			j++;
		}
		ft_redir_iter(g_data->pipes[i].head_red);
		*/
		replace_dollar_varables(g_data, i);
		i++;
	}
	return (handle_rediractions(g_data));
}
