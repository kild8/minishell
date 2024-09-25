#include "minishell.h"

//ATTENTION il faut FREE chaque string et aussi chaque token donc double free car double malloc

void	parsing_input(char *str, t_command **command)
{
	/*char *new_str;

	new_str = clean_string(str);
	check_quotes(new_str);
	check_errors();
	create_command(new_str, command);*/

	create_command(str, command);
}

void	create_command(char *str, t_command **command)
{
	t_command	*new;
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		while (is_white_space(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		new = malloc(sizeof(t_command));
		/*if (!new)
			free_and_exit();*/
		initialize_command(new);
		fill_command(str + i, new);
		append_to_list_command(command, new);
		i = i + command_length(str + i); // attention a cette ligne si lindex est faux
	}
	print_commands(command);
	set_pipeout(command);
}

void print_redir_list(t_list_redir *list, const char *redir_type)
{
    t_list_redir *current = list;
    int i = 0;

    if (current == NULL)
    {
        printf("  No %s redirection\n", redir_type);
        return;
    }

    printf("  %s redirection:\n", redir_type);
    while (current != NULL)
    {
        printf("    %s[%d]: %s\n", redir_type, i, current->str); // assuming `path` is a member in t_list_redir
        current = current->next;
        i++;
    }
}

void print_commands(t_command **head)
{
    t_command *current = *head;

    printf("TEST:\n");
    while (current != NULL)
    {
        // Imprimer les arguments
        printf("Arguments:\n");
        if (current->arg != NULL)
        {
            for (int i = 0; current->arg[i] != NULL; i++)
            {
                printf("  arg[%d] = %s\n", i, current->arg[i]);
            }
        }
        else
        {
            printf("  No arguments\n");
        }

        // Vérifier les pipes
        if (current->pipein)
        {
            printf("  Pipe input\n");
        }
        else
        {
            printf("  No pipe input\n");
        }

        if (current->pipeout)
        {
            printf("  Pipe output\n");
        }
        else
        {
            printf("  No pipe output\n");
        }

        // Imprimer les listes de redirections
        print_redir_list(current->list_heredoc, "heredoc");
        print_redir_list(current->list_infile, "infile");
        print_redir_list(current->list_outfile, "outfile");

        // Passer à l'élément suivant
        current = current->next;
        printf("\n");  // Ajouter une ligne vide entre les commandes
    }
}

void	set_pipeout(t_command **head)
{
    t_command *current = *head;
	while (current != NULL)
	{
		if (current->pipein == true)
			current->next->pipeout = true;
		current = current->next;
	}
	return ;
}

void	initialize_command(t_command *new)
{
	new->arg = NULL;
	new->pipein = false;
	new->pipeout = false;
	new->list_heredoc = NULL;
	new->list_infile = NULL;
	new->list_outfile = NULL;
	new->next = NULL;
}

void	fill_command(char *str, t_command *command)
{
	command->arg = create_tab_for_command(str);
	check_for_redir(str, command);
}

char	**create_tab_for_command(char *str)
{
	char	**tb;
	int		i;

	i = 0;
	tb = malloc((count_arg(str) + 1) * sizeof(char*));
	printf("%d ceci est le nb dargument", count_arg(str));
	/*if (!tab)
		free_and_exit(command);*/
	while (i < count_arg(str))
	{
		tb[i] = create_string(str, i);
		i++;
	}
	tb[i] = NULL;
	return(tb);
}
//on est deja envoyer au bon endroit
char	*create_string(char *str, int c)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	j = 0;
	len = arg_length(str, c);
	printf("%d\n", len);
	new = malloc((len + 1) * sizeof(char));
	/*if (!new)
		free_and_exit();*/
	i = i + skip_white_space(str + i);
	i = i + skip_redir(str + i);
	while (c > 0)
	{
		i = i + skip_arg(str + i);
		i = i + skip_redir(str + i);
		c--;
	}
	while (j < len)
	{
		new[j] = str[i + j];
		j++;
	}
	new[len] = '\0';
	return (new);
}

void	append_to_list_command(t_command **command, t_command *new)
{
	t_command	*current;

	current = *command;
	
	if (current == NULL)
		*command = new;
	if (current != NULL)
	{
		while (current->next)
			current = current->next;
	current->next = new;
	}
	return ;
}
void	check_for_redir(char *str, t_command *command)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && !is_separator(str[i]))
			i++;
		if (str[i] != '\0')
		{
			if (str[i] == '|')
				command->pipein = true;
			else if (str[i] == '<' && str[i + 1] == '<')
			{
				create_list_heredoc(str + i, command);
				i++;
			}
			else if (str[i] == '<')
				create_list_infile(str + i, command);
			else if (str[i] == '>')
				create_list_outfile(str + i, command);
			i++;
		}
	}
	return ;
}

// /!\ ATTENTION GERER LES EXIT ET FREE ENCORE
//SI JAMAIS les outfile et infile ne
//sarrete pas a lespace mais copie tout jusqa la fin ou la pipe