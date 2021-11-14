#include "ft_minishell.h"

char	**ft_args_append_find_end(t_node *node)
{
	char	**end;

	if (node->flags && node->args)
		end = ft_strsjoin(node->flags, node->args);
	else if (!node->flags && node->args)
		end = ft_strscopy(node->args);
	else if (node->flags && !node->args)
		end = ft_strscopy(node->flags);
	else
		end = 0;
	return (end);
}

void	ft_args_append(t_node *node)
{
	char	**command;
	char	**new_args;
	char	**end;

	end = ft_args_append_find_end(node);
	if (node->args)
		ft_strsfree(node->args);
	if (node->command)
	{
		command = ft_strscreate(node->command);
		if (end)
		{
			new_args = ft_strsjoin(command, end);
			ft_strsfree(command);
			ft_strsfree(end);
			node->args = new_args;
		}
		else
			node->args = command;
	}
}

int	ft_find_flag(const char **args, const char *flag)
{
	(void)args;
	(void)flag;
	return (1);
}
