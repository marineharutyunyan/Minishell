#include "mini.h"

int	get_pipes_count(char *str)
{
	int		count;
	int		i;
	char	c;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i] != '\0')
			{
				i++;
			}
		}
		else if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

void	split_by_pipes(t_general *g_data, t_parsing *data)
{
	int		i;
	char	c;
	int		strt;
	int		pipes_count;

	data->pipe_count = get_pipes_count(g_data->line);
	data->pipes = malloc(sizeof(char *)
			* (data->pipe_count + 2));
	data->pipes[data->pipe_count + 1] = NULL;
	i = 0;
	pipes_count = 0;
	strt = i;
	while (g_data->line[i] != '\0')
	{
		i = pass_quotes(g_data->line, i);
		if (g_data->line[i] == '|')
		{
			data->pipes[pipes_count] = ft_substr(g_data->line, strt, i - strt);
			pipes_count++;
			strt = i + 1;
		}
		i++;
	}
	if (g_data->line[i] == '\0')
		data->pipes[pipes_count] = ft_substr(g_data->line, strt, i - strt);
}
