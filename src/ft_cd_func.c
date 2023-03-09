/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:33:21 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/06 21:10:36 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_cd(char **ptr)
{
	int i;

	i = 0;
	if(ptr[i] == NULL)
	{
		printf("%s\n", ("HOME"));
	}
	while(ptr[i])
	{
		if (chdir(ptr[i]) < 0)
		printf("%s\n", strerror(errno));
		i++;
	}
}