#include "ft_minishell.h"

int	ft_execve_buildin_1(t_env *env, t_node *node)
{
	if (node->command && !ft_strcmp(node->command, "export"))
	{
		ft_export(node, env);
		if (env->n_pipes > 0)
			exit(0);
		return (1);
	}
	if (node->command && !ft_strcmp(node->command, "unset"))
	{
		ft_unset(node, env);
		if (env->n_pipes > 0)
			exit(0);
		return (1);
	}
	if (node->command && !ft_strcmp(node->command, "pwd"))
	{
		ft_pwd(env);
		if (env->n_pipes > 0)
			exit(0);
		return (1);
	}
	return (0);

}

int	ft_execve_buildin_2(t_env *env, t_node *node)
{
	if (node->command && !ft_strcmp(node->command, "cd"))
	{
		ft_cd(node, env);
		if (env->n_pipes > 0)
			exit(0);
		return (1);
	}
	if (node->command && !ft_strcmp(node->command, "echo"))
	{
		ft_echo(node, env);
		if (env->n_pipes > 0)
			exit(0);
		return (1);
	}
	if (node->command && !ft_strcmp(node->command, "env"))
	{
		ft_env(env);
		if (env->n_pipes > 0)
			exit(0);
		return (1);
	}
	if (node->command && !ft_strcmp(node->command, "exit"))
	{
		ft_exit(env);
		if (env->n_pipes > 0)
			exit(0);
		return (1);
	}
	return (0);
}

void	ft_execve(t_env *env, t_node *node)
{
	int	pid;

	if (env->n_pipes > 0)
	{
		// pid = fork();
		// if (pid == 0)
		// {
			ft_execve_buildin_1(env, node);
			ft_execve_buildin_2(env, node);
			if (execve(node->path_command, node->exec_args, env->envp) == -1)
				exit(0);
		// }
		// waitpid(0,0,0);
		if (env->n_pipes > 0)
		{
			exit(0);
		}
	}
	else
	{
		if (ft_execve_buildin_1(env, node) == 1)
			return;
		else if (ft_execve_buildin_2(env, node) == 1)
			return;
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(node->path_command, node->exec_args, env->envp) == -1)
				{
					printf("Command not found!\n");
					exit(0);
				}
			}
			waitpid(0,0,0);
		}
	}
}
