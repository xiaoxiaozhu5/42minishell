#include "ft_minishell.h"

void	ft_exit(t_env *env)
{
	env->last_status = 0;
	ft_destroy_env(env);
	exit(0);
}
