#include "mini.h"

// void print_unexpected_error(char c)
// {
// 	ft_printf(2, "syntax error near unexpected token '%c'", c);
// }

// if returning '1' closing pair missing if '0' either the the quote dose not exist in str at all or have closing symbol and is valid
int check_opening_closing_quote_pair(char *str)
{
	int i;
	char c;

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

int check_unexpected(char *str)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = -1;
	flag = 0;

	while (str[i])
	{
		while (i != j)
		{
			j = i;
			i = pass_quotes(str, i);
			flag = 1;
		}
		if (str[i] && (flag == 0 || (str[i + 1] == '\0')) && ft_strchr(UNEXPECTED, str[i]))
			return (1);
		if (str[i] && !ft_strchr(METACHARACTERS, str[i]))
			flag = 1;
		else if (flag == 1 &&  str[i] && ft_strchr(UNEXPECTED, str[i]))
			flag = 0;
		if (str[i])
			i++;
	}
	return (0);
}

int has_errors(char *str)
{
	str = ft_trim(str); // TODO free
	if (check_opening_closing_quote_pair(str) == 1
		|| (check_unexpected(str) == 1  && printf("check_unexpected\n"))
		|| check_redir_sytax(str) == 1)
	{
		ft_printf(2, "Minishell: syntax error near unexpected token\n");
		free(str);
		return (1);
	}
	free(str);
	return (0);
}