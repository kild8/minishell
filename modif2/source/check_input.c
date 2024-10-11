#include "minishell.h"

bool	check_input(char **input, t_envp **envp, t_data *data)
{
	if (check_quote(*input))
	{
		write(1, "Error: quotes are wrong\n", 24);
		return (true);
	}
	dollar_checker(input, envp, data);
	return (false);
}
