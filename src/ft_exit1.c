/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:13:53 by lohanyan          #+#    #+#             */
/*   Updated: 2023/03/06 21:10:36 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
void	ft_check_sign1(char **ptr, int i)
{
	if(ft_strcmp(&ptr[i][1], "9223372036854775808") > 0)
	{
		printf("exit\n");
		printf("Minishell: exit %s : numeric argument required\n", ptr[i]);
		exit(255);
	}
}

void	ft_check_sign(char **ptr, int i)
{
	if (ft_strcmp(&ptr[i][1], "9223372036854775807") > 0)
	{
		printf("exit\n");
		printf("Minishell: exit %s : numeric argument  required\n", ptr[i]);
		exit(255);
	}
	else if (ft_strcmp(ptr[i], "9223372036854775807") > 0)
	{
		printf("Minishell : exit %s : numeric argument required\n", ptr[i]);
		printf("exit\n");
		exit(255);
	}
}

void	ft_print_error_for_exit(char **ptr, int i)
{
	printf("Minishell: exit %s : numeric argument required\n", ptr[i]);
	exit(255);
}

void	ft_print_error_for_two_arguments(void)
{
	printf("exit\n");
	exit(0);
}
