#include "mini.h"

char	*ft_strdup_modif(const char *s1, int startIndex, int len)
{
	char	*str;
	int		i;
	
	i = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == 0)
		return (0);
	while (len != 0)
	{
		str[i] = s1[startIndex];
		startIndex++;
		len--;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_trim(char *s1)
{
	int		i;
	int		len;
	int		startIndex;
	int 	endIndex;

	len = ft_strlen(s1);
	if (len > 0)
	{
		i = 0;
		while (s1[i] == 32 && s1[i] != '\0')
		{
			i++;
		}
		startIndex = i;
		if(startIndex == len)
		{
			return (ft_strdup("")); 
		}
		i = len-1;
		while (s1[i] == 32 && i != 0)
		{
			i--;
		}
		endIndex = i + 1;
		return (ft_strdup_modif(s1, startIndex, endIndex  - startIndex));
	}
	return (ft_strdup("")); 
}