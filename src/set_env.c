#include "mini.h"

int	pass_key(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && (ft_isalpha(line[i])
			|| ft_isdigit(line[i]) || line[i] == '_'))
	{
		i++;
	}
	if (line[i] == '=')
		i++;
	return (i);
}

char	*get_key(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && (ft_isalpha(line[i])
			|| ft_isdigit(line[i]) || line[i] == '_'))
		i++;
	if (i > 0)
	{
		return (ft_substr(line, 0, i));
	}
	return (NULL);
}

char	*get_value(char *line)
{
	int	start_index;
	int	i;

	start_index = pass_key(line);
	i = start_index;
	while (line[i] != '\0')
	{
		i++;
	}
	if (i > start_index)
	{
		return (ft_substr(line, start_index, i - start_index));
	}
	return (ft_strdup(""));
}

//Variable decleration - variables are limityed to be letters _ and numbers 
void	set_env_t_list(t_general *g_data, char **env)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (env[i])
	{
		key = get_key(env[i]);
		value = get_value(env[i]);
		if (g_data->head_env == NULL)
			g_data->head_env = lst_env_new(key, value);
		else
			lst_env_add(&g_data->head_env, lst_env_new(key, value));
		i++;
		free(key);
		free(value);
	}
	lst_env_add(&g_data->head_env, lst_env_new("?", "0")); // TODO review
	// t_env * tmp = g_data->head_env;
	// while (tmp)
	// {
	// 	printf("tmp = %s\n",tmp->key);
	// 	printf("tmp = %s\n",tmp->value);
	// 	tmp = tmp->next;
	// }
}
