#include "minishell.h"




en fait il faut dabord creer  une chiane listee avec 
la commande et ses arguments car il peuvent venir au fur et a mesure
puis on convertit cette chaine en un tableau de char**
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


char	**create_tab(char *input, t_command **command)
{
	char **tab;
	int	size;

	size = count_arg(input);
	tab = malloc((size + 1) * sizeof(char*));
	return (tab);
}
	if is quote
	create str quote
	else
	create str no quote