#include "mini.h"

int	free_array(void	**ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (1);
}

int	free_double_array(void	***ptr)
{
	int i;
	char **temp =(char **)*ptr;

	i = 0;
	if (temp == NULL)
		return (1);
	while(temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	*ptr = NULL;
	return (1);
}
