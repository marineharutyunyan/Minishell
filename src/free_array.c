/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lohanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:47:34 by lohanyan          #+#    #+#             */
/*   Updated: 2023/03/16 16:50:55 by lohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini.h"

int	free_array(void	**ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (1);
}

int	free_double_array(void	***ptr)
{
	int		i;
	char	**temp;


	i = 0;
	temp = (char **)*ptr;
	if (temp == NULL)
		return (1);
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	*ptr = NULL;
	return (1);
}
