/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:22:24 by faggar            #+#    #+#             */
/*   Updated: 2021/11/26 17:45:00 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/param.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>

// Constants
# define SHELL_NAME				"42minishell"
# define ERROR_UNEXPECTED_TOKEN	"syntax error near unexpected token"
# define ERROR_CMD_NOT_FOUND	"command not found"
# define ERROR_IDENTIFIER		"not a valid identifier"
# define ERROR_HOMELESS			"home path does not exist"
# define STRING_QUOTE			'*'
# define REDIRECT_LEFT			0b00000001
# define REDIRECT_RIGHT 		0b00000010
# define REDIRECT_DOUBLE_LEFT	0b00000100
# define REDIRECT_DOUBLE_RIGHT	0b00001000

// Structures

typedef struct s_lol
{
	int	i;
	int	*pid;
	int	**p;
}t_lol;


typedef struct s_node
{
	void	*next;
	void	*redirs;
	char	*command;
	char	**flags;
	char	**args;
	char	**exec_args;
	char	c_end;
	int		redir_1;
	int		redir_0;
	char	*path_command;
	int		fds[2];
}	t_node;

typedef struct s_redir
{
	void	*next;
	int		type;
	char	*value;
}	t_redir;

typedef struct s_env
{
	char	**envp;
	t_node	*cmds;
	char	**execve_paths;
	int		last_status;
	int		n_pipes;
}	t_env;

// External functions
void	rl_replace_line(const char *text, int clear_undo);

// Lists
t_node	*ft_node_create();
t_redir	*ft_node_redir_create();
void	*ft_list_create_back(void **lst, void *new);
void	ft_list_print(t_node **list);

// History
void	ft_init_history();
void	ft_add_history(char *line);

// Parser
int		ft_preparser(char *input);
char	*ft_parser(char *input, t_env *env);
char	*ft_get_value(const char *key, char **envp);
char	*ft_unusual_dollar(char *input, t_env *env, int *i);

// Builder
void	ft_build_cmds(t_node **cmds, char *input);
t_node	*ft_build_cmd(char *input, int *start, int *end);

// Cleaners
void	ft_clear_cmds(t_env *env);
void	ft_destroy_env(t_env *env);

// Builder Utilities
int		ft_find_flags_length(const char *str, int i);
int		ft_next_redir(const char *input, int start, int end);
int		ft_args_end(const char *input, int start, int end);
// sfdfss

// Builder Utilities Second
char	**ft_split_args(char const *args);

// Preprocess
void	ft_preprocess(t_env *env);

// Process
void	ft_process(t_env *env);
void	ft_execve(t_env *env, t_node *node);

// Build-in(s)
void	ft_export(t_node *node, t_env *env);
void	ft_unset(t_node *node, t_env *env);
void	ft_pwd(t_env *env);
void	ft_cd(t_node *node, t_env *env);
void	ft_echo(t_node *node, t_env *env);
void	ft_env(t_env *env);
void	ft_exit(t_node *node, t_env *env);

// Envp Utils
char	*ft_get_key(const char *key_value);
int		ft_find_key(char **envp, const char *key_value);
void	ft_envp_add(char ***envp, const char *key_value);
void	ft_envp_update(char ***envp, const char *key_value);

// Errors
int		ft_error_unexpected_token(char token);
void	ft_error_cmd_fail(const char *cmd_name);
void	ft_error_identifier(const char *cmd_name, char identifier);
void	ft_error_homeless(const char *cmd_name);
void	ft_strerror(const char *error_msg1, const char *error_msg2);

// Utils
int		ft_is_split(const char *input, int i);
int		ft_next_word_starts_with(const char *str, const char *set, int s);
char	*ft_rm_whitespace(char *input);

// Helpers
int		ft_str_find_alnum(char *str, int index_start);
int		ft_str_find_in_word(char *str, char c, int start);
char	*ft_rm_whitespace(char *input);

// Execution Arguments
void	ft_exec_args(t_node *node);

int		**arr_of_fd_and_pids(int count_pipes, int **arr_pid);
void	make_redirrect(t_node *cur_cmd, t_env *env);
char	*find_path1(t_env *data, t_node *iter);
void	ft_new_pipe(t_env *data);

void	simple_right(t_redir *redir, t_node *cmd_info);
int		simple_left(t_redir *redir, t_node *cmd_info);
void	double_right(t_redir *redir, t_node *cmd_info);
void	sigint_r(int signal);
void	sigquit_r(int signal);
void	redir_sig();
void	check_heredock(t_redir *redirs);
int		double_left(t_redir *redir);
void	make_heredeock(t_redir *redir);
#endif