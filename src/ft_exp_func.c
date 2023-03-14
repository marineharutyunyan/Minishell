/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:27:40 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/14 11:09:22 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_exp_func(char **ptr, t_general *data, int j, int i)
{
	char	**tmp;
	
	while (ptr && ptr[i])
	{
		if(ft_errors_for_export(ptr[i]) != 1)
		{
			if (ft_strchr(ptr[i], '=') != NULL)
				get_env(data, ptr[i]);
			if (ft_check_str(ptr[i], data) == 0)
			{
				tmp = data->exp;
				j = 0;
				while (tmp && tmp[j])
					j++;
				data->exp = malloc(sizeof(char *) * (j + 2));
				j = 0;
				while (tmp[j])
				{
					data->exp[j] = ft_strdup(tmp[j]);
					j++;
				}
				data->exp[j] = ft_epstrdup(ptr[i]);
				data->exp[j + 1] = NULL;
				ft_free_exp(&tmp, j);
			}
			set_env_t_list(data, data->env);
		}
		i++;
	}
}

void	ft_free_exp(char ***tmp, int j)
{
	j = 0;
	while ((*tmp)[j])
	{
		free((*tmp)[j]);
		j++;
	}
	free(*tmp);
}
