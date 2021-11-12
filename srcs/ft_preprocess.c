#include "ft_minishell.h"

void	ft_preprocess(t_env *env)
{
	t_node *iter;

	iter = env->cmds;
	while (iter)
	{
		if (iter->c_end == '|')
			env->n_pipes++;
		iter = iter->next;
	}
}
