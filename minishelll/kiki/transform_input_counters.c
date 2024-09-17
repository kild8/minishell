#include "minishell.h"

int		count_commands(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while(is_white_space(str[i]))
			i++;
		if (str[i] != '\0')
		{
			count++;
			while (!is_separator(str[i]) && str[i] != '\0')
				i++;
		}
		while (is_separator(str[i]) && str[i] != '\0')
			i++;
	}
	return (count);
}

int		count_arguments(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0' && !is_separator(str[i]))
	{
		while (is_white_space(str[i]))
			i++;
		if (str[i] != '\0' && !is_separator(str[i]))
			count++;
		while (!is_white_space(str[i]) && str[i] != '\0' && !is_separator(str[i]))
			i++;
	}
	return (count);
}

bool	is_separator(char c)
{
	if (c == ';')
		return (true);
	if (c == '|')
		return (true);
	return (false);
}

bool	is_white_space(char c)
{
	if (c == ' ')
		return (true);
	if (c == '\t')
		return (true);
	if (c == '\n')
		return (true);
	if (c == '\r')
		return (true);
	if (c == '\v')
		return (true);
	if (c == '\f')
		return (true);
	return (false);
}

bool	is_arguments()
{


}