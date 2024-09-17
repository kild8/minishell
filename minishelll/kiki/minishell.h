#ifndef MINISHELL_H
#define MINISHELL_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_command
{
	char	**arg;
	bool	in_redir;
	char	*in_path;
	bool	out_redir;
	char	*out_path;
	bool	append;
}	t_command;

#endif