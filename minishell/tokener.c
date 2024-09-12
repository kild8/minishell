#include <stddef.h>
#include <stdbool.h>

typedef struct s_token
{
	char			*str;
	struct s_token 	*next;
}	t_token;

//le but est de separer la string en elements
//les elements sont separes selon si on trouve un signe de commande
//donc faire une fonction this is a sign == is_separator
//on separe ces elements dans une chaine listees
//preparer une structure pour les token

//ATTENTION il faut FREE chaque string et aussi chaque token donc double free car double malloc

//dans un deuxieme temps les token seront convertis dans une liste de commandes a executer

void	separator(char *str, t_token **tok)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_separator(str[i]))
			create_token((tok, str + i));
		i++;
	}
}
//lis jusqua ce quon trouve un des separateurs
//envoie le string dans la fonction create token
//continue tant que le string est pas terminer


bool	is_separator(char c)
{
	if (c == 'X')
		return (true);
	return (false);
}

void	create_token(t_token **tok, char *str)
{
	t_token	new;

	new = malloc(sizeof(t_token));
	if (!new)
		free_and_exit();
	initialize_token(new);
	create_string_for_token(str, *new);
	append_token(new, tok);
}

initialize_token(t_token *tok)
{
	tok->str = NULL;
	tok->next = NULL;
}

void	(t_token **tok, t_token *new)
{
	t_token	*last;

	last = NULL;
	if (token->next == NULL)
		tok = new;
	else
	{
		last = get_last_token(t_stack *tok);
		last->next = new;
	}
}

create_string_for_token(char *str, t_token **tok)
{
	char	*new;
	int		i;

	while (!is_separator(str[i]))
		i++;
	new = malloc(sizeof((i + 1) * char));
	if (!new)
		free_and_exit();
	new = strncpy(str);
	new[i] = '\0';
	tok->str = new;
}

t_token	*get_last_token(t_token *tok)
{
	t_token	*current;

	current = tok;
	while (current->next)
		current = current->next;
	return (current);
}

void	free_and_exit()
{
	


}