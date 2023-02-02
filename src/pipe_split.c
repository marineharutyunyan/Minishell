#include "mini.h"

int get_pipes_count(char *str)
{
    int count;
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
			while (str[i] != c  && str[i] != '\0')
			{
				i++;
			}
		}
        else if (str[i] == '|')
        {
            count++;
        }
		i++;
	}
    return (count);
}

void 	split_by_pipes(t_general *g_data, t_parsing *data)
{
    int		i;
	char	c;
    int     start_index;
    int     pipes_count;

    data->pipe_count = get_pipes_count(g_data->line);
    data->pipes = malloc(sizeof(char *) * (data->pipe_count + 2));
    data->pipes[data->pipe_count + 1] = NULL;
	i = 0;
    pipes_count = 0;
    start_index = i;
	while (g_data->line[i] != '\0')
	{
		if (g_data->line[i] == '\'' || g_data->line[i] == '"')
		{
			c = g_data->line[i++];
			while (g_data->line[i] != c  && g_data->line[i] != '\0')
				i++;
		}
        else if (g_data->line[i] == '|')
        {
            data->pipes[pipes_count] = ft_substr(g_data->line, start_index, i - start_index);
            pipes_count++;
            start_index = i + 1;
        }
		i++;
	}
    if (g_data->line[i] == '\0')
        data->pipes[pipes_count] = ft_substr(g_data->line, start_index, i - start_index);
	g_data->parse_data = data;
}
