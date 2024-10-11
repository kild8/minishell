#include "minishell.h"

void	setup(int ac, char **av, char **env, t_envp **envp)
{
	(void)ac;
	(void)av;
	*envp = ft_copy_envp(env);
	setup_signals();
}
