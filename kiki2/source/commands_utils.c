#include "minishell.h"

int	command_length(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !is_pipe(str[i]))
		i++;
	if (is_pipe(str[i]))
		i++;
	return (i);

}
int	arg_length(char *str, int c)
{
	int	i;

	i = 0;
	while (c > 0)
	{
		i = i + skip_arg(str + i);
		i = i + skip_redir(str + i);
		c--;
	}
	return (i);
}
int	count_arg(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	i = i + skip_white_space(str + i);
	while (str != '\0'&& !is_pipe(str[i]))
	{
		i = i + skip_redir(str + i);
		i = i + skip_white_space(str + i);
		if (str != '\0'&& !is_separator(str[i])
				&& !is_white_space(str[i]) && !is_pipe(str[i]))
			count++;
		while (str != '\0'&& !is_separator(str[i])
				&& !is_white_space(str[i]) && !is_pipe(str[i]))
				i++;
		i = i + skip_white_space(str + i);
	}
	return (count);
}

int	skip_redir(char *str)
{
	int	i;

	i = 0;
	if (is_separator(str[i]))
	{
		while (str != '\0')
		{
			while (is_separator(str[i]))
				i++;
			i = i + skip_white_space(str + i);
			while (!is_white_space(str[i]))
				i++;
			i = i + skip_white_space(str + i);
			if (is_separator(str[i]))
				continue ;
			else
				break ;
		}
	}
	/*par redir on entend ca commence par un separateur et ensuite
	il y a un certain nombre despace
	puis un certain nombre de char
	puis un certain nombre despace
	puis un separateur*/
	return (i);
}

int	skip_white_space(char *str)
{
	int	i;

	i = 0;
	while (is_white_space(str[i]))
		i++;
	return (i);
}

int	skip_arg(char *str)
{
	int	i;
	i = 0;

	i = skip_white_space(str + i);
	while (!is_white_space(str + i))
		i++;
	return (i);
}