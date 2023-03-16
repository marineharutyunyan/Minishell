/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:28:34 by maharuty          #+#    #+#             */
/*   Updated: 2023/03/16 20:28:34 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// 0 line is valid and invalid if returning 1
//TODO is this correct way to check the rediractions 
//TODO functions functionality is not tested 
// ""ssdfs "sdgdf ">>ddfg 
int	check_redir_sytax(char *str)
{
	int		i;
	char	c;
	int		j;

	i = 0;
	j = -1;
	while (str[i] != '\0')
	{
		while (i != j)
		{
			j = i;
			i = pass_quotes(str, i);
		}
		if (str[i] && ft_strchr(REDIRECTIONS, str[i]))//TODO all defined's like  REDIRECTIONS have \0 in last character case, make sure this conndition doesn't disturb any logic  
		{
			c = str[i];
			if (str[i + 1] == '\0')
				return (1);
			else if (str[i + 1] == c)
				i++;
			i++;
			i = pass_spces(str, i);
			if (str[i] == '\0')
				return (1);
			if (str[i] && ft_strchr(METACHARACTERS, str[i]))
				return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}
