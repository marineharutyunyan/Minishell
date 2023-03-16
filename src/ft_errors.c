/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:20:52 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/16 14:57:07 by lohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_errors_for_export(char *str)
{
	int	i;

	i = 0;
	
	if((!(str[0] >= 65 && str[0] <= 90)) && (!(str[0] >= 97 && str[0] <= 122)) && (str[0] != '_'))
	{
		printf("not a valid identifier\n");
		return (1);
	}
	else
	{
		i++;
		while(str && str[i] && str[i] != '=' && str[i - 1] != '+')
		{
			if(str[i] == '+' && str[i + 1] != '=')
			{
				printf("minishell: export: %s: not a valid identifier\n", str);
				return (1);
			}
			if((!(str[i] >= 65 && str[i] <= 90)) && (!(str[i] >= 97 && str[i] <= 122)) && (str[i] != '_') && str[i] != '+' &&  (!(str[i] >= 48 && str[i] <= 57)))
			{
				printf("not a valid identifier\n");
				return (1);
			}
			i++;
		}
	}
	return(0);

}

