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

void	ft_exit(char **ptr)
{
	int						i;
	int						j;
	unsigned long long int	tiv;
	unsigned char			sign;

	i = 1;
	j = 0;
	sign = tiv;
	if (!ptr[i])
		ft_print_error_for_exit();
	tiv = ft_atoi_modifed(ptr[i]);
	if (ft_check_exit(&ptr[i], i, j) != 0)
		return ;
	if (ft_strlen(ptr[i]) > 20)
		ft_print_error_for_two_arguments(ptr, i);
	if (ptr[i][0] == '-')
		ft_check_sign1(ptr, i);
	else if (ptr[i][0] == '+')
		ft_check_sign(ptr, i);
	printf("exit\n");
	exit(tiv);
}

int	ft_check_exit(char **ptr, int i, int j)
{
	if (ptr[0][0] == '-' || ptr[0][0] == '+')
		j++;
	//printf("%s\n", ptr[i]);
	while (ptr[0][j])
	{
		//printf("aaaaaaaaaaa\n");
		if (!(ptr[0][j] >= 48 && ptr[0][j] <= 57))
		{
			//printf("aaaaaaaaaa\n");
			//printf("exit\n");
			printf("Minishell: exit: %s : numeric argument required\n", ptr[i]);
			exit(255);
		}
		j++;
	}
	if (ptr[i] != NULL)
	{
		//printf("llllllll\n");
		printf("exit\n");
		printf("Minishell : exit: too many arguments\n");
		return (1);
	}
	//printf("%s\n", ptr[0]);
	//printf("%s\n", ptr[i]);
	//printf("%s\n", ptr[i + 1]);
	return (0);
}
