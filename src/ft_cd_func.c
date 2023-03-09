/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:33:21 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/09 23:20:00 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_cd(char **ptr)
{
	int i;

	i = 0;
	if(ptr[i] == NULL)
	{
		printf("%s\n", ("HOME")); // delete
	}
	while(ptr[i])
	{
		if (chdir(ptr[i]) < 0)
		{
			printf("%s\n", strerror(errno));
			return (1);
		}
		i++;
	}
	return (0);
}
