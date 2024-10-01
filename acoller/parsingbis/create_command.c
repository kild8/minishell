#include "minishell.h"

int	create_command(char *input, t_temp_command **command)
{
	int			i;
	char		*str;
	t_temp_command	*new;
	t_temp_command	*current;

	i = skip_command_length(input);
	new = malloc(sizeof(t_temp_command));
	str = copy_command(input);
	new->str = str;
	if (*command == NULL)
		*command = new;
	else
	{
		current = *command;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (i);
}

int	skip_command_length(char *str)
{
	int	i;

	i = 0;
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (!is_white_space(input[i]) && input[i] != '\0')
		i++;
	return (i);
}

int	command_length(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (!is_white_space(input[i]) && input[i] != '\0')
	{
		i++;
		c++;
	}
	return (c);
}

char *copy_command(char *input)
{
	int		i;
	int		j;
	int		len;
	char 	*copy;

	i = 0;
	j = 0;
	len = command_length(input);
	copy = malloc((len + 1 )* sizeof(char));
	if (!copy)
		return (NULL);
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (!is_white_space(input[i]) && input[i] != '\0')
	{
		copy[j] = input[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
