#include "minishell.h"

void	convert_command(t_temp_command **temp, t_command **command, t_inpath **inpath, t_outpath **outpath, char input)
{
	t_temp_command	*current;
	int				size;
	char			**tab;
	int				i;
	
	current = *temp;
	size = command_count(temp);
	tab = create_tab(size);
	i = 0;
	while (i < size)
	{
		tab[i] = current->str;
		current->str = NULL;
		current = current->next;
		i++;
	}
	create_command_def(tab, command, inpath, outpath, input);
	free_temp_command(temp);
	return ;
}

int	command_count(t_temp_command **command)
{
	t_temp_command	*current;
	int				i;
	
	current = *temp;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void	create_command_def(char **tab, t_command **command, t_inpath **inpath, t_outpath **outpath, char input)
{
	t_command	*new;
	t_command	*current;

	new = malloc(sizeof(t_command));
	init_command(new);
	if (input == '|')
		new->pipeout = true;
	new->inpath = *inpath;
	new->outpath = *outpath;
	new->arg = tab;
	if (*command == NULL)
		*command = new;
	else
	{
		current = *command;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return ;
}

void	free_temp_command(t_temp_command **command)
{
	t_temp_command *current;
	t_temp_command *next;

	current = *command;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	return ;
}


void	init_command(t_command *new)
{
	new->arg = NULL;
	new->inpath = NULL;
	new->outpath = NULL;
	new->pipein = false;
	new->pipeout = false;
	new->next = NULL;
}

char	**create_tab(int size)
{
	char	**tab;

	tab = malloc((size + 1) * sizeof(char*));
	if (!tab)
		return (NULL);
	tab[size] = NULL;
	return (tab);
}

	if is quote
	create str quote
	else
	create str no quote