#include "ft_minishell.h"

void	ft_exit(t_node *node, t_env *env)
{
	short int	status;

	if (node->args && node->args[0])
		status = ft_atoi(node->args[0]);
	else
		status = 0;
	env->last_status = status;
	ft_destroy_env(env);
	exit(status);
}
