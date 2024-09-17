#include "minishell.h"
//le but est de separer la string en elements
//les elements sont separes selon si on trouve un signe de commande
//donc faire une fonction this is a sign == is_separator
//on separe ces elements dans un tableau qui contient les commandes

//ATTENTION il faut FREE chaque string et aussi chaque token donc double free car double malloc

char	***transform_input(char *str)
{
	int		i;
	char	***commands;

	i = 0;
	create_command(commands, str + i);
	while (str[i])
	{
		if (is_separator(str[i]))
			create_command((commands, str + i));
		i++;
	}
	return (commands);
}
//lis jusqua ce quon trouve un des separateurs
//envoie le string dans la fonction create token
//continue tant que le string est pas terminer


void	create_commands(char ***commands, char *str)
{
	char	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		free_and_exit();
	initialize_token(new);
	create_string_for_token(str, *new);
	append_token(new, tok);
}

create_string_for_command(char *str, t_token **tok)
{
	char	*new;
	int		i;

	while (!is_separator(str[i]))
		i++;
	new = malloc((i + 1) * sizeof(char));
	if (!new)
		free_and_exit(tok);
	new = ft_strncpy(str, i);
	new[i] = '\0';
	tok->str = new;
}
