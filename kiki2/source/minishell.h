/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:39:19 by joseluis          #+#    #+#             */
/*   Updated: 2024/09/25 14:08:15 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit
# include <unistd.h>     // write, access, open, read, close, fork, dup, dup2, pipe, getcwd, chdir, unlink, execve, isatty
# include <fcntl.h>      // open, O_ constants
# include <sys/wait.h>   // wait, waitpid, wait3, wait4
# include <signal.h>     // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>     // opendir, readdir, closedir
# include <sys/stat.h>   // stat, lstat, fstat
# include <string.h>     // strerror
# include <termios.h>    // tcsetattr, tcgetattr, ioctl
# include <curses.h>     // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (ou <termcap.h> selon la version)
# include <readline/readline.h>   // readline, add_history
# include <readline/history.h>    // rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <sys/ioctl.h>  // ioctl
# include <term.h>       // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <stddef.h>
# include <stdbool.h>

typedef struct s_command
{
	char					**arg;
	bool					pipein;
	bool					pipeout;
	struct s_list_redir		*list_heredoc;
	struct s_list_redir		*list_infile;
	struct s_list_redir		*list_outfile;
	struct s_command	*next;
}	t_command;

typedef struct	s_list_redir
{
	char				*str;
	bool				append;
	struct s_list_redir	*next;
}	t_list_redir;

typedef struct s_data
{
	int			*exit_status;
	int			base_stdin;
	int			base_stdout;
	struct s_envp		**envp;
	struct s_command	**command;
}	t_data;

typedef struct s_envp
{
	char			*var;
	struct s_envp	*pre;
	struct s_envp	*next;
}	t_envp;

int		check_open_quote(char *str);
char	*ft_change_str(char *old, char *convert, int start, int size);
int		dollar_converter(char **str, int i, char **env);
void	exit_statut(char *str, int i);
void	dollar_checker(char **str, char **env);

void	ft_copy_envp(char **env, t_envp **envp);
t_envp	*ft_new_var(char *str);
void	ft_add_back(t_envp **envp, t_envp *new);
void	ft_env(t_envp **envp);
void	ft_free_envp(t_envp *envp);

void	ft_pre_export(t_envp **envp, char **args);
void	ft_export(t_envp **envp, char *arg);
void	ft_pre_unset(t_envp **envp, char **args);
void	ft_unset(t_envp **envp, char *arg);
int		ft_strlen_var(char *str);

void	start_exec(t_command **command, t_envp **envp);


int		command_length(char *str);
int		arg_length(char *str, int c);
int		count_arg(char *str);
bool	is_separator(char c);
bool	is_pipe(char c);
bool	is_white_space(char c);
void	parsing_input(char *str, t_command **command);
void	create_command(char *str, t_command **command);
void	print_commands(t_command **head);
void print_redir_list(t_list_redir *list, const char *redir_type);
void	initialize_command(t_command *new);
void	fill_command(char *str, t_command *command);
char	**create_tab_for_command(char *str);
char	*create_string(char *str, int c);
void	append_to_list_command(t_command **command, t_command *new);
void	check_for_redir(char *str, t_command *command);
void	create_list_heredoc(char *str, t_command *command);
void	create_list_infile(char *str, t_command *command);
void	create_list_outfile(char *str, t_command *command);
char	*create_list_element(char *str);
void	append_to_list_redir(t_list_redir **list, t_list_redir *new);
void	set_pipeout(t_command **head);


void	setup_signals();

#endif