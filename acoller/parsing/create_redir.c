#include "minishell.h"

int	create_redir(char *input, t_inpath **inpath, t_outpath **outpath)
{
	int	i;

	i = 0;
	if (*input == '<')
		i = create_inpath(input, inpath);
	else if (*input == '>')
		i = create_outpath(input, outpath);
	return (i);
}


int	create_inpath(char *input, t_inpath **inpath)
{
	int			i;
	char		*filename;
	t_inpath	*new;
	t_inpath	*current;

	i = filename_length(input);
	new = malloc(sizeof(t_inpath));
	filename = copy_redir(input);
	new->filename = filename;
	if (*input == '<' && *(input + 1) == '<')
		new->heredoc = true;
	else
		new->heredoc = false;
	if (*inpath == NULL)
		*inpath = new;
	else
	{
		current = *inpath;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (i);
}


int	create_outpath(char *input, t_outpath **outpath)
{
	int		i;
	char		*filename;
	t_outpath	*new;
	t_outpath	*current;

	i = filename_length(input);
	new = malloc(sizeof(t_outpath));
	filename = copy_redir(input);
	new->filename = filename;	
	if (*input == '>' && *(input + 1) == '>')
		new->append = true;
	else
		new->append = false;
	if (*outpath == NULL)
		*outpath = new;
	else
	{
		current = *outpath;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (i);
}

int	filename_length(char *input)
{
	int	i;

	i = 0;
	while (is_redir(input[i]) && input[i] != '\0')
		i++;
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (!is_white_space(input[i]) && input[i] != '\0')
		i++;
	return (i);
}

char *copy_redir(char *input)
{
	int		i;
	int		j;
	int		len;
	char 	*copy;

	i = 0;
	j = 0;
	len = filename_length(input);
	copy = malloc((len + 1 )* sizeof(char));
	if (!copy)
		return (NULL);
	while (is_redir(input[i]) && input[i] != '\0')
		i++;
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
