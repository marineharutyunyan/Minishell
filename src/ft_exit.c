/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:56:44 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/16 20:03:50 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// 9223372036854775808

int	ft_exit(char **ptr, t_env *head_env)
{
	int						i;
	int						j;
	unsigned long long int	tiv;
	unsigned char			sign;

	i = 1;
	j = 0;
	if (!ptr[i] && ft_printf(2, "exit\n"))
		exit(ft_atoi(get_value_by_key("?", head_env)));
	tiv = ft_atoi_modifed(ptr[i]);
	if (ft_check_exit(&ptr[i], i, j) != 0)
		return (1);
	if (ptr[i][0] == '-')
		ft_check_sign1(ptr, i);
	else if (ptr[i][0] == '+' || ptr[i][0] != '-')
		ft_check_sign(ptr, i);
	ft_printf(2, "exit\n");
	exit(tiv);
	return (0);
}

int	ft_check_exit(char **ptr, int i, int j)
{
	if (ptr[0][0] == '-' || ptr[0][0] == '+')
		j++;
	while (ptr[0][j])
	{
		if (!(ptr[0][j] >= 48 && ptr[0][j] <= 57))
		{
			printf("Minishell: exit: %s : numeric argument required\n", ptr[0]);
			exit(255);
		}
		j++;
	}
	if (ptr[i] != NULL)
	{
		printf("exit\n");
		printf("Minishell : exit: too many arguments\n");
		return (1);
	}
	return (0);
}
