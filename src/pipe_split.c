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

void    split_by_pipes(t_parsing *data, char *str)
{
    data->pipe_count = get_pipes_count(str);
    data->pipes = malloc(sizeof(char *) * data->pipe_count +1);

    int		i;
	char	c;
    int     start_index;
    int     pipes_count;

	i = 0;
    pipes_count = 0;

    start_index = i;
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
        else if (str[i] == '|' || str[i] == '\0')
        {
            data->pipes[pipes_count] = ft_substr(str, start_index, i - start_index);
            pipes_count++;
            start_index = i + 1;
        }
		i++;
	}
    if (str[i] == '\0')
        data->pipes[pipes_count] = ft_substr(str, start_index, i - start_index);
}