//cree les listes de heredoc
//cree les listes de out avec append oui non
//cree les liste de in

#include "minishell.h"

void	create_list_heredoc(char *str, t_command *command)
{
	t_list_redir	*new;

	new = malloc(sizeof(t_list_redir));
	new->next = NULL;
	new->append = false;
	new->str = create_list_element(str);
	append_to_list_redir(&command->list_heredoc, new);
}

void	create_list_infile(char *str, t_command *command)
{
	t_list_redir	*new;

	new = malloc(sizeof(t_list_redir));
	new->next = NULL;
	new->append = false;
	new->str = create_list_element(str);
	append_to_list_redir(&command->list_infile, new);
}

void	create_list_outfile(char *str, t_command *command)
{
	t_list_redir	*new;

	new = malloc(sizeof(t_list_redir));
	new->next = NULL;
	if (*(str + 1) == '>')
		new->append = true;
	else
		new->append = false;
	new->str = create_list_element(str);
	append_to_list_redir(&command->list_outfile, new);
}

void	append_to_list_redir(t_list_redir **list, t_list_redir *new)
{
	t_list_redir	*current;

	current = *list;
	
	if (current == NULL)
		*list = new;
	if (current != NULL)
	{
		while (current->next)
			current = current->next;
	current->next = new;
	}
	return ;
}


char	*create_list_element(char *str)
{
	char 	*elem;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (is_separator(str[i]) || is_white_space(str[i]))
		i++;
	elem = malloc((arg_length(str + i, 0) + 1) * sizeof(char));
	while (str[i] != '|' && str[i] != '\0' && !is_white_space(str[i]))
	{
		elem[j] = str[i];
		i++;
		j++;
	}
	elem[j] = '\0';
	return (elem);
}
