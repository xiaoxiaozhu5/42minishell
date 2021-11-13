#include "ft_minishell.h"

void	ft_echo(t_node *node, t_env *env)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (node->flags && ft_strnstr(node->flags, "-n", ft_strlen(node->flags)) == 0)
	{
		n_flag = 1;
	}
//	while (node->args && node->args[i])
//	{
//		printf("%s ", cmd[i]);
//		i++;
//	}
//	if (n_flag == false)
//		ft_printf("\n");
	env->last_status = 0;
}
