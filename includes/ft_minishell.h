#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// Constants
# define SHELL_NAME "42minishell"
# define ERROR_UNEXPECTED_TOKEN "syntax error near unexpected token"
# define ERROR_CMD_FAIL "command not found"

// Typedefs

// Structures
typedef struct s_node
{
	void	*next;
	char	*command;
	char	*flags;
	char	*args;
	char	c_end;
} t_node;

typedef struct s_env
{
	t_node	**cmds;
	int		def;
	int		numb_pipes;
}	t_env;

// Lists
t_node	*ft_list_create_back(t_node **lst);

// History
void	ft_init_history();
void	ft_add_history(char *line);

// Parser
int		ft_preparser(char *input);
char	*ft_parser(char *input, char **envp);
char	*ft_get_value(const char *key, char **envp);
char	*ft_digit_dollar(char *input, int *i);

// Builder
void	ft_build_cmds(t_env *env, char *input);

// Process
void	ft_process(t_env *env);

// Utils
int		ft_error_unexpected_token(char token);
void	ft_error_cmd_fail(const char *cmd_name);

#endif