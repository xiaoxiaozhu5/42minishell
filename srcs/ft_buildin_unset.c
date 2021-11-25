#include "ft_minishell.h"

int	ft_is_correct_unset(const char *arg)
{
	int	i;

	if (!arg)
		return (1);
	i = 0;
	if (arg[0] == '=' || ft_isdigit(arg[0]))
	{
		ft_error_identifier("unset", arg[i]);
		return (0);
	}
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			ft_error_identifier("unset", arg[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ft_last_address(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (strs + (i - 1));
}

void	ft_unset_env_string(char ***envp, const char *key_value)
{
	int		exists_index;
	char	**last_address;
	char	**exists_address;

	exists_index = ft_find_key(*envp, key_value);
	if (exists_index != -1)
	{
		last_address = ft_last_address(*envp);
		exists_address = *envp + exists_index;
		free(*exists_address);
		*exists_address = *last_address;
		*last_address = 0;
	}
}

void	ft_unset(t_node *node, t_env *env)
{
	int		i;

	if (node->args)
	{
		i = -1;
		while (node->args[++i])
		{
			if (!ft_is_correct_unset(node->args[i]))
			{
				env->last_status = 1;
				return ;
			}
		}
		i = -1;
		while (node->args[++i])
			ft_unset_env_string(&env->envp, node->args[i]);
		env->last_status = 0;
	}
}
