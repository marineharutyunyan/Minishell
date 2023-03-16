/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:33:21 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/16 18:09:04 by lohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
int	ft_cd(char **ptr, t_general *data)
{
	int	i;
	int	j;
	char *tmp;
	int sign;

	i = 0;
	j = 0;
	sign = 0;
	if (ptr[i + 1] == NULL)
	{
		if(get_value_by_key("HOME", data->head_env) == NULL)
		{
			ft_printf(2, "minishell: cd: %s: %s\n", "HOME not set");
		}
		else
		{
			chdir(get_value_by_key("HOME", data->head_env));
			return (0);
		}
		// while (data->env[i])
		// {
		// 	if (ft_strcmp(data->env[i], "HOME=/Users/lohanyan") == 0)
		// 	{
		// 		while (data->env[i][j])
		// 		{	
		// 			if (data->env[i][j] == '=')
		// 				sign = j;
		// 			j++;
		// 		}
		// 		tmp = ft_substr(data->env[i], (sign + 1), j);
		// 		printf("%s\n", tmp);
		// 		chdir(tmp);
		// 		free(tmp);
		// 	}
		// 	i++;
		// }
	}
	else if (chdir(ptr[i + 1]) < 0)
	{
		ft_printf(2, "minishell: cd: %s: %s\n", ptr[i + 1], strerror(errno));
		return (1);
	}
	return (0);
}
