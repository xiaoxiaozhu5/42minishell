#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/param.h>

// Constants
# define DEBUG_MODE				1
# define SHELL_NAME				"42minishell"
# define ERROR_UNEXPECTED_TOKEN	"syntax error near unexpected token"
# define ERROR_CMD_FAIL			"command not found"
# define STRING_QUOTE			'*'
# define REDIRECT_LEFT			0b00000001
# define REDIRECT_RIGHT 		0b00000010
# define REDIRECT_DOUBLE_LEFT	0b00000100
# define REDIRECT_DOUBLE_RIGHT	0b00001000

// Typedefs

// Structures
typedef struct s_node
{
	void	*next;
	void	*redirs;
	char	*command;
	char	*flags;
	char	*args;
	char	c_end;
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
	t_node	**cmds;
	char	*username;
	int		last_status;
	int		numb_pipes;
}	t_env;

typedef struct s_echo_data
{
	char	*cmd;
	char	*flag;
	char	*str;
	char	*redirr_type;
	char	*file_name;
	int		pipe;
	int		fd;

	char	**path;
	char	**flags;
	char	**env;
	int		fds[2];
	pid_t	pid;

	// cd
	char	**args;
	char	*pwd_old;
	char	*pwd_cur;

	int		count_pipes;

	//temp variables for tests pipe
	char	***commands;
	int 	exit;

	int		redirect_1;
	int		redirect_0;
}t_data;

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
void	ft_build_cmds(t_env *env, char *input);
t_node	*ft_build_cmd(char *input, int *start, int *end);

// Builder Utilities
int		ft_find_flags_length(const char *str, int i);
int		ft_next_redir(const char *input, int start, int end);
int		ft_args_end(const char *input, int start, int end);
void	ft_add_redir(t_redir **list, char *input, int *k, int *end);

// Process
void	ft_process(t_env *env);

// Utils
int		ft_error_unexpected_token(char token);
void	ft_error_cmd_fail(const char *cmd_name);
int		ft_is_split(const char *input, int i);
int		ft_next_word_starts_with(const char *str, const char *set, int s);

// Redir utilities
int		ft_cmp(char *s1, char *s2);
//echo
char	*ft_echo(t_data *data);


int		fill_env_path(t_data *data, char **env);

//		PIPE
void	ft_pipe(t_data *data, char ***args);
//*********************
int	ft_get_env(t_data *data);
int	ft_get_pwd(t_data *data);


int	**arr_of_fd_and_pids(int count_pipes, int **arr_pid);


#endif