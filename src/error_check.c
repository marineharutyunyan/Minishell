/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lohanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:41:25 by lohanyan          #+#    #+#             */
/*   Updated: 2023/03/16 16:42:57 by lohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini.h"

// void print_unexpected_error(char c)
// {
// 	ft_printf(2, "syntax error near unexpected token '%c'", c);
// }

// if returning '1' closing pair missing if '0' either the the quote dose not exist in str at all or have closing symbol and is valid
int	check_opening_closing_quote_pair(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i] != '\0')
			{
				i++;
			}
			if (str[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	has_errors(char *str)
{
	str = ft_trim(str); // TODO free
	if (check_opening_closing_quote_pair(str) == 1
		|| (check_unexpected(str) == 1)
		|| check_redir_sytax(str) == 1)
	{
		ft_printf(2, "Minishell: syntax error near unexpected token\n");
		free(str);
		return (1);
	}
	free(str);
	return (0);
}
