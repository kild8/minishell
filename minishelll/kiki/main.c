#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	***commands;
	char	*input;
	int		i;

	commands = NULL;
	while (1)
	{
	input = readline("minishell >");
	if (!input)
		break;
	if (*input)
		add_history(input);
	commands = transform_input(input);
	i = 0;
	while (commands[i] != NULL)
	{
		execve(commands[i][0], commands[i], envp);
		i++;
	}
	}
	return (0);
}

execve
**char

***char
liste chainee
execve()

