#include "ft_minishell.h"

void	ft_print_declare(const char *str)
{
	int		i;
	int		is_value_started;
	int		exists_equal;

	i = 0;
	is_value_started = 0;
	exists_equal = 0;
	ft_putstr_fd("declare -x ", 1);
	while (str[i])
	{
		if (str[i] == '=' && !is_value_started)
		{
			ft_putchar_fd('=', 1);
			i++;
			ft_putchar_fd('\"', 1);
			exists_equal = 1;
			is_value_started = 1;
		}
		else
			ft_putchar_fd(str[i++], 1);
	}
	if (exists_equal)
		ft_putchar_fd('\"', 1);
	ft_putchar_fd('\n', 1);
}

int	ft_export_print(char **strs)
{
	int		i;
	char	**strs_copy;

	i = 0;
	strs_copy = ft_strscopy(strs);
	if (!strs_copy)
		return (1);
	ft_strssort(strs_copy);
	while (strs_copy[i])
	{
		ft_print_declare(strs_copy[i]);
		free(strs_copy[i]);
		i++;
	}
	free(strs_copy);
	return (0);
}

int	ft_is_correct_import(const char *arg)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
	{
		ft_error_identifier("export", arg[0]);
		return (0);
	}
	while (arg[i])
		i++;
	if (arg[i] != '=')
	{
		while (arg[i])
		{
			if (!(arg[i] == '\t' || arg[i] == ' '))
			{
				ft_error_identifier("export", arg[i]);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

void	ft_export(t_node *node, t_env *env)
{
	int		i;

	if (!node->args[1])
		env->last_status = ft_export_print(env->envp);
	else
	{
		i = 0;
		while (node->args[++i])
		{
			if (!ft_is_correct_import(node->args[i]))
			{
				env->last_status = 1;
				return ;
			}
		}
		i = 0;
		while (node->args[++i])
			ft_envp_add(&(env->envp), node->args[i]);
		env->last_status = 0;
	}
}
