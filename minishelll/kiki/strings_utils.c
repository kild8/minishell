#include "minishell.h"

char	*ft_strncpy(char *str, int i)
{
	char	*copy;
	int		j;

	j = 0;
	while (j < i)
	{
		copy[j] = str[j];
		j++;
	}
	return (copy);
}