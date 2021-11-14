#include "ft_minishell.h"

void	ft_exit(t_env *env)
{
	ft_destroy_env(env);
	exit(0);
}
