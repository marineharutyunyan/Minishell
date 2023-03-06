/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_modified.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:14:54 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/06 21:20:14 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
// char	*ft_strchr(char *s, int c)
// {
// 	int		i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == (char) c)
// 			return ((char *)s + i);
// 		i++;
// 	}
// 	if (c != '\0')
// 		return (0);
// 	return ((char *)s + i);
// }

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	return (s1[i] - s2[i]);
// }

unsigned long long int	ft_atoi_modifed(const char *str)
{
	int						index;
	int						sign;
	unsigned long long int	value;

	index = 0;
	sign = 1;
	value = 0;
	while (str[index] == 32 || (str[index] >= 9 && str[index] <= 13))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = -sign;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		value = value * 10 + str[index] - '0';
		index++;
	}
	return (sign * value);
}

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	return (0);
// }
