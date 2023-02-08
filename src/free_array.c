#include "mini.h"

int	free_array(void	**ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (1);
}
