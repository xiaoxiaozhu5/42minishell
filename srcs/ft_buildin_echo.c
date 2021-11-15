#include "ft_minishell.h"

void	ft_echo(t_node *node, t_env *env)
{
	int	i;

	i = 0;
	while (node->args && node->args[i])
	{
		if (node->args[i + 1])
			printf("%s ", node->args[i]);
		else
			printf("%s", node->args[i]);
		i++;
	}
	if (!node->flags || !ft_strsfind(node->flags, "-n"))
		printf("\n");
	env->last_status = 0;
}
