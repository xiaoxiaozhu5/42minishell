#include "ft_minishell.h"

void	ft_args_append(t_node *node)
{
	int		i;
	char	**new_args;

	if (node->command && node->args)
	{
		new_args = ft_strscopy_append(node->args, node->command, 0);
		ft_strsfree(node->args);
		node->args = new_args;
	}
	else if (node->command && !node->args)
		node->args = ft_strscreate(node->command);
	if (node->flags)
	{
		i = -1;
		while (node->flags[++i])
		{
			new_args = ft_strscopy_append(node->args, node->flags[i], 0);
			ft_strsfree(node->args);
			node->args = new_args;
		}
	}
}

int	ft_find_flag(const char **args, const char *flag)
{
	(void)args;
	(void)flag;
	return (1);
}
