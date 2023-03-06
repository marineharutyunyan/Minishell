/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:31:28 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/06 21:17:17 by maharuty         ###   ########.fr       */
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
	//str = ft_sign(s1, &i, &j, &flag);
	str = (char *)malloc((ft_strlen(s1) + 3) * sizeof(char));
	if (str == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		if ( s1[i] == '=' && flag == 0 && s1[i + 1] != '\"')
		{
			if (s1[i - 1] == '+')
				j--;
			flag = 1;
			str[j++] = s1[i++];
			str[j++] = '\"';
		}
		else
		{

			if (s1[i - 1] == '+' && plus == 0)
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

char	*ft_strjoin_modifed(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s1 || !s2)
		return (0);
	while (s1[i] != '\0')
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(s1);
	return (str);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!s1 || !s2)
		return (0);
	while (s1[i] != '\0')
	{
		if (s1[i] && s1[i] == '\"' && s1[i - 1] != '=')
			i++;
		if (s1[i])
		{
			str[j] = s1[i];
			j++;
			i++;
		}
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\"';
	str[j + 1] = '\0';
	free(s1);
	s1 = NULL;
	return (str);
}
