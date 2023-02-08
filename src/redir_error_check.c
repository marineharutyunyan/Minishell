#include "mini.h"

// 0 line is valid and invalid if returning 1
//TODO is this correct way to check the rediractions 
//TODO functions functionality is not tested 
int	check_redir_sytax(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] != '\0')
	{
		pass_quotes(str, i);
		if (str[i] == '>')
		{
			if (str[i + 1] != '\0')
				return (1);
			else if (str[i + 1] != '\0' && str[i + 1] == '>')
				i++;
			i++;
			if (ft_strchr(METACHARACTERS, str[i]))
				check_redir_sytax(str + i);
			else
				return (1);
		}
		i++;
	}
	return (0);
}
