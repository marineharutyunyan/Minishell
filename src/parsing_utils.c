#include "mini.h"

int	pass_spces(char *line, int i)
{
	while (line[i] != '\0' && ft_strchr(SPACE, line[i]))
		i++;
	return (i);
}

int	pass_single_quotes(char *str, int i)
{
	char	c;

	if (str[i] == '\'')
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

int	pass_word(char *line, int i)
{
	while (line[i] != '\0' && !ft_strchr(METACHARACTERS, line[i]))
	{
		i = pass_quotes(line, i);
		i++;
	}
	return (i);
}

char	*get_word(char *line, int *i)
{
	int	start_index;

	start_index = *i;
	while (line[*i] != '\0' && !ft_strchr(METACHARACTERS, line[*i]))
	{
		*i = pass_quotes(line, *i);
		(*i)++;
	}
	if ((*i) > start_index)
		return (ft_substr(line, start_index, (*i) - start_index));
	else
		return (NULL);
}

int	pass_redir(char *line, int i)
{
	if (ft_strchr(REDIRECTIONS, line[i]))
	{
		while (line[i] != '\0' && ft_strchr(REDIRECTIONS, line[i]))
			i++;
		i = pass_spces(line, i);
		i = pass_word(line, i);
		i = pass_spces(line, i);
	}	
	return (i);
}
