/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:50:23 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/06 21:12:40 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_new_malloc(char *str, char **tmp, int i, int flag)
{
	free(tmp[i]);
	tmp[i] = 0;
	if (flag == 1)
		tmp[i] = ft_epstrdup(str);
	else if (flag == 0)
		tmp[i] = ft_strdup(str);
}

int	ft_check_str(char *str, t_general *data)
{
	int		i;
	char	*tmp;
	int		sign;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	if (str[i] == '=' && str[i - 1] == '+')
		i--;
	tmp = ft_substr(str, 0, i);
	sign = i;
	if (ft_cut_for_exp(data, tmp, str, sign) == 1)
		return (1);
	free(tmp);
	return (0);
}

int	ft_check_str1(char *str, t_general *data)
{
	int		i;
	char	*tmp;
	int		sign;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	if (str[i] == '=' && str[i - 1] == '+')
		i--;
	tmp = ft_substr(str, 0, i);
	sign = i;
	i = 0;
	if (ft_cut_for_env(data, tmp, str, sign) == 1)
		return (1);
	free(tmp);
	return (0);
}
