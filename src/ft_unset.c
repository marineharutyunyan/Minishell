/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:42:39 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/06 21:12:40 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int ep_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '=')
		i++;
	return (i);
}

int	ft_free(char **ptr, char **tmp, int *i)
{
	int len;

	if (ep_strlen(*ptr) <= ep_strlen(*tmp))
		len = ep_strlen(*tmp);
	else
		len = ep_strlen(*ptr);
	if (ft_strncmp(*ptr, *tmp, len) == 0)
	{
		free(*tmp);
		*tmp = 0;
		free(*ptr);
		*ptr = 0;
		return (*i);
	}
	return (-1);
}

int	ft_check_str2(char *str, char **exp)
{
	int		i;
	char	*ptr;
	char	*tmp;
	int		j;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	tmp = ft_substr(str, 0, i);
	i = 0;
	while (exp[i])
	{
		j = 0;
		while (exp[i][j] && exp[i][j] != '=')
			j++;
		ptr = ft_substr(exp[i], 0, j);
		j = ft_free(&ptr, &tmp, &i);
		free(ptr);
		if(j > -1)
			return (j);
		i++;
	}
	free(tmp);
	return (-1);
}

void	ft_check_exp(int k, t_general *data)
{
	int		j;
	int		l;
	char	**tmp;

	j = 0;
	l = -1;
	if (k >= 0)
	{
		tmp = data->exp;
		while (tmp[j])
			j++;
		data->exp = malloc(sizeof(char *) * j);
		j = 0;
		while (tmp && tmp[j])
		{
			if (j == k)
				j++;
			else
				data->exp[++l] = ft_strdup(tmp[j++]);
		}
		data->exp[l + 1] = NULL;
	}
}

void	ft_unset(t_general *data, char *str)
{
	int		i;
	int		j;
	char	**ptr;
	int		k;
	int		l;

	i = 0;
	k = 0;
	ptr = ft_split(str, ' ');
	while (ptr && ptr[i])
	{
		ft_unset_for_env(data, ptr[i]);
		l = 0;
		j = 0;
		k = ft_check_str2(ptr[i], data->exp);
		//k = ft_free(ptr, data->exp, &i);
		ft_check_exp(k, data);
		i++;
	}
}

void	ft_unset_for_env(t_general *data, char *ptr)
{
	int		j;
	char	**tmp;
	int		k;
	int		l;

	k = 0;
	l = 0;
	j = 0;
	k = ft_check_str2(ptr, data->env);
	if (k >= 0)
	{
		tmp = data->env;
		while (tmp[j])
			j++;
		data->env = malloc(sizeof(char *) * j);
		j = 0;
		ft_check_env(k, data, tmp);
		j = -1;
		while(tmp[++j])
		{
			free(tmp[j]);
			tmp[j] = NULL;
		}
		free(tmp);
	}
}
