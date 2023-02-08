#include "mini.h"

//line = smole lines in between pipes 
//index = index of the which in between pipe text it is
void	set_args(t_general *g_data, char *line, int index)
{
	int		i;
	int		j;
	char	*word;

	g_data->pipes[index].argv = malloc(sizeof (char *)
			* (g_data->pipes[index].words_count + 1));
	g_data->pipes[index].argv[g_data->pipes[index].words_count] = NULL;
	i = 0;
	j = 0;
	word = NULL;
	while (line[i] != '\0')
	{
		i = pass_spces(line, i);	
		i = pass_redir(line, i);
		word = get_word(line, &i);
		if (word != NULL)
		{
			g_data->pipes[index].argv[j] = word;
			j++;
			// TODO the free is not working here why 
			// free(word);
			// free_array((void **)&word);
		}
	}
}

int	get_redir_flag(char *line, int i)
{
	int		flag;

	i = pass_spces(line, i);
	flag = 9; //some random false flag value 
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
	return (flag);
}

// dhgsdfhs >> dfgsd > fhgfgh   |
//line = smole lines in between pipes 
//index = index of the which in between pipe text it is
void	set_rediractions(t_pipe pipe, char *line)
{
	int		temp_start_index;
	int		i;
	int		flag;
	char	*word;

	i = -1;
	temp_start_index = 0;
	while (line[++i] != '\0')
	{
		flag = get_redir_flag(line, i);
		if (line[i] != '\0')
		{
			i = pass_spces(line, i);
			pipe.words_count += 1;
			get_word(line, &i);
		}
		//TODO add check for redirection validity
		if (flag != 9)
		{
			i = pass_spces(line, i);
			word = get_word(line, &i);
			if (pipe.head_red == NULL)
				pipe.head_red = lst_redir_new(word, flag);
			else
				lst_redir_add_back(&pipe.head_red, lst_redir_new(word, flag));
		}
	}
}

void	paresing(t_general *g_data)
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
		set_rediractions(g_data->pipes[i], g_data->parse_data.pipes[i]);
		set_args(g_data, g_data->parse_data.pipes[i], i);
		j = 0;
		while (g_data->pipes[i].argv[j])
		{
			printf("argv = %s\n", g_data->pipes[i].argv[j]);
			j++;
		}
		// for printing 
		//ft_redir_iter(g_data->pipes[i].head_red);
		i++;
	}
}
