#include "mini.h"

void	print_unexpected_error(char c)
{
	ft_printf(2, "syntax error near unexpected token '%c'", c);
}

int	check_first_symbol(char *str)
{
	int	i;

	i = 0;
	while (UNEXPECTED[i])
	{
		if (str[0] == UNEXPECTED[i])
		{
			print_unexpected_error(str[0]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_last_symbol(char *str)
{
	int	len;
	len = ft_strlen(str);
	if (len != 0 && str[len - 1] == '|')
	{
		print_unexpected_error(str[len - 1]);
		return (1);
	}
	return (0);
}

//if returning '1' closing pair missing if '0' either the the quote dose not exist in str at all or have closing symbol and is valid
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
			{
				print_unexpected_error(c);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	has_errors(char *str)
{
	str = ft_trim(str);
	if (!check_first_symbol(str))
	{
		if (!check_opening_closing_quote_pair(str))
		{
			if (!check_last_symbol(str))
			{
				if (!check_redir_sytax(str))
				{
					return (0);
				}
			}
		}
	}
	return (1);
}
