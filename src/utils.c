/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:31:28 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/17 00:03:36 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (str == 0)
		return (0);
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup1(char *s1)
{
	char	*str;
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (str == 0)
		return (0);
	while (s1 && s1[i] != '\0')
	{
		if (s1[i] == '+' && s1[i + 1] && s1[i + 1] == '=' && flag == 0)
		{
			flag += 1;
			i++;
		}
		else
		{
			str[j] = s1[i];
			i++;
			j++;
		}
	}
	str[j] = '\0';
	return (str);
}

char	*ft_epstrdup(char *s1)
{
	char	*str;
	int		i;
	int		j;
	int		flag;
	int		plus;

	i = 0;
	j = 0;
	flag = 0;
	plus = 0;
	if (!s1)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + 3) * sizeof(char));
	if (str == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		if (s1[i] == '=' && flag == 0 && s1[i + 1] != '\"')
		{
			if (s1[i - 1] == '+')
				j--;
			flag = 1;
			str[j++] = s1[i++];
			str[j++] = '\"';
		}
		else
		{
			if (i != 0 && s1[i - 1] == '+' && plus == 0)
				j--;
			str[j++] = s1[i++];
			plus = 1;
		}
	}
	if (flag == 1 && s1[i - 1] != '\"')
	{
		str[j] = '\"';
		str[j + 1] = '\0';
	}
	else
		str[j] = '\0';
	return (str);
}
