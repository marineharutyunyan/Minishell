/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:56:44 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/06 21:19:07 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_exit(char *str)
{
	int						i;
	int						j;
	char					**ptr;
	unsigned long long int	tiv;
	unsigned char			sign;

	i = 0;
	j = 0;
	ptr = ft_split(str, ' ');
	tiv = ft_atoi_modifed(str);
	sign = tiv;
	if (!ptr[i])
		ft_print_error_for_two_arguments();
	if (ft_strlen(str) > 20)
		ft_print_error_for_exit(ptr, i);
	if (ft_check_exit(str, i, j))
		return ;
	if (ptr[i][0] == '-')
		ft_check_sign1(ptr, i);
	else if (ptr[i][0] == '+')
		ft_check_sign(ptr, i);
	printf("exit\n");
	exit(tiv);
}

int	ft_check_exit(char *str, int i, int j)
{
	char	**ptr;

	ptr = ft_split(str, ' ');
	if (ptr[i][0] == '-' || ptr[i][0] == '+')
		j++;
	while (ptr[i][j])
	{
		if (!(ptr[i][j] >= 48 && ptr[i][j] <= 57))
		{
			printf("exit\n");
			printf("Minishell: exit: %s : numeric argument required\n", ptr[i]);
			exit(255);
		}
		j++;
	}
	if (ptr[i + 1] != NULL)
	{
		printf("exit\n");
		printf("Minishell : exit: too many arguments\n");
		return (1);
	}
	return (0);
}
