#include "mini.h"

char	*get_inbetween_double_quotes_text(char *str, int *i)
{
	char	c;
	int		start_index;
	char	*text;

	start_index = (*i);
	text = NULL;
	if (str[(*i)] == '"')
	{
		c = str[(*i)];
		(*i)++;
		while (str[(*i)] != c && str[(*i)] != '\0')
		{
			(*i)++;
		}
		text = ft_substr(str, start_index + 1, (*i) - (start_index + 1));
		(*i)++;
	}
	return (text);
}

char	*get_inbetween_single_quotes_text(char *str, int *i)
{
	char	c;
	int		start_index;
	char	*text;

	start_index = (*i);
	text = NULL;
	if (str[(*i)] == '\'')
	{
		c = str[(*i)];
		(*i)++;
		while (str[(*i)] != c && str[(*i)] != '\0')
		{
			(*i)++;
		}
		text = ft_substr(str, start_index + 1, (*i) - (start_index + 1));
		(*i)++;
	}
	return (text);
}

int	pass_quotes(char *str, int i)
{
	char	c;

	if (str[i] == '\'' || str[i] == '"')
	{
		c = str[i];
		i++;
		while (str[i] != c && str[i] != '\0')
		{
			i++;
		}
	}
	return (i);
}
