/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sign.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:43:13 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/06 21:10:36 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_sign(char *s1, int *i, int *j, int *flag)
{
	int		plus;
	char	*str;

	plus = 0;
	str = (char *)malloc((ft_strlen(s1) + 3) * sizeof(char));
	while (s1 && s1[*i] != '\0')
	{
		if (s1[*i] == '=' && *flag == 0 && s1[(*i) + 1] && s1[(*i) + 1] != '\"')
		{
			if (*i != 0 && s1[(*i) - 1] == '+')
				*j -= 1;
			*flag = 1;
			str[(*j)++] = s1[(*i)++];
			str[(*j)++] = '\"';
		}
		else
		{
			if (*i != 0 && s1[(*i) - 1] == '+' && plus == 0)
				(*j)--;
			str[(*j)++] = s1[(*i)++];
			plus = 1;
		}
	}
	return (str);
}
