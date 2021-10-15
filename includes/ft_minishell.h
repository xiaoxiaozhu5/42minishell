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

// Constants
# define ERROR "Error!\n"

// Typedefs

// Structures
typedef struct s_env
{
	int	def;
	int	numb_pipes;
}	t_env;

// History
void	ft_init_history();
void	ft_add_history(char *line);

// Parser
t_env	*ft_parser(char *input);

// Process
void	ft_process(t_env *env);

#endif