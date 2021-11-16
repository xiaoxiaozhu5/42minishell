#include "ft_minishell.h"

void	ft_execve_buildin_1(t_env *env, t_node *node)
{
	if (node->command && !ft_strcmp(node->command, "export"))
	{
		ft_export(node, env);
		exit(0);
	}
	if (node->command && !ft_strcmp(node->command, "unset"))
	{
		ft_unset(node, env);
		exit(0);
	}
	if (node->command && !ft_strcmp(node->command, "pwd"))
	{
		ft_pwd(env);
		exit(0);
	}
}

void	ft_execve_buildin_2(t_env *env, t_node *node)
{
	if (node->command && !ft_strcmp(node->command, "cd"))
	{
		ft_cd(node, env);
		exit(0);
	}
	if (node->command && !ft_strcmp(node->command, "echo"))
	{
		ft_echo(node, env);
		exit(0);
	}
	if (node->command && !ft_strcmp(node->command, "env"))
	{
		ft_env(env);
		exit(0);
	}
	if (node->command && !ft_strcmp(node->command, "exit"))
	{
		ft_exit(env);
		exit(0);
	}
}

int	ft_execve(t_env *env, t_node *node)
{
	// ft_execve_buildin_1(env, node);
	// ft_execve_buildin_2(env, node);
	return (execve(node->path_command, node->exec_args, env->envp));
}
