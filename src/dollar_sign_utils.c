#include "mini.h"

char	*get_variable_name(char *line, int *i)
{
	int	start_num;

	start_num = (*i);
	while (line[(*i)] != '\0' && (ft_isalpha(line[(*i)])
			|| ft_isdigit(line[(*i)]) || line[(*i)] == '_'))
		(*i)++;
	if ((*i) > start_num)
		return (ft_substr(line, start_num, (*i) - start_num));
	return (NULL);
}

char	*find_value_by_key(char *key, t_env *lst)
{
	while (lst)
	{
		if (ft_strcmp(key, lst->key) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

char	*process_line(char *line, t_general *g_data)
{
	int		i;
	char	*final_line;
	char	*temp;
	//TODO take kare avout freeing temp
	i = 0;
	temp = NULL;
	final_line = NULL;
	while (line[i] != '\0')
	{
		temp = get_inbetween_single_quotes_text(line, &i);
		final_line = ft_strjoin(final_line, temp);
		temp = get_inbetween_double_quotes_text(line, &i);
		if (!temp)
			temp = get_text(line, &i);
		if (temp)
		{
			temp = replace_env_var(temp, g_data);
			final_line = ft_strjoin(final_line, temp);
		}
	}
	return (final_line);
}

//$HOME help "hello $aa"$MM text$

char	*replace_env_var(char *line, t_general *g_data)
{
	int		i;
	char	*final_line;
	char	*temp;

	i = 0;
	final_line = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			i++;
			temp = get_variable_name(line, &i);
			if (temp != NULL)
				final_line = ft_strjoin(final_line,
						find_value_by_key(temp, g_data->head_env));
			else if (line[i] == '\0')
				final_line = ft_strjoin(final_line, "$");
		}
		if (line[i] && line[i] != '$')
			final_line = ft_strjoin(final_line, char_to_string(line[i]));
		if (line[i] != '\0' && line[i] != '$')
			i++;
	}
	return (final_line);
}
