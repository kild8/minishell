#include "minishell.h"

void	parsing(char *input, t_command **command)
{
	t_temp_command 	*temp_cmd;
	t_inpath		*inpath;
	t_outpath		*outpath;
	int				length;

	temp_cmd = NULL;
	inpath = NULL;
	outpath = NULL;

	check_open_quotes;
	check_errors;

	length = 0;
	while (input[i] != '\0')
	{
		while (input != '|' && input[i] != '\0')
		{
			length = 0;
			while (is_white_space(input[i]))
				i++;
			if (is_redir(input[i]))
				length = create_redir(input[i], &inpath, &outpath);
			else if (input[i] != '\0')
				length = create_command(input[i], &temp_cmd);
			else if (input[i] == '\0')
				break ;
			i = i + length;
			if (length == 0)
				i++;
		}
		convert_command(&temp_cmd, command, &inpath, &outpath, input + i);
	}
}

bool	check_open_quotes(char *input)
{
	int	i;
	char first_q;
	char sec_q;

	i = 0;
	first_q = 'a';
	sec_q = 'a';
	while (str[i] != '\0')
	{
		if (first_q == 'a' && str[i] == '\'')
			first_q = 's';
		else if (first_q == 'a' && str[i] == '"')
			first_q = 'd';
		else if (first_q != 'a' )
	}
}