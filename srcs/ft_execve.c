/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:13:14 by faggar            #+#    #+#             */
/*   Updated: 2021/11/27 14:14:36 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (0);
}

int	ft_execve_buildin_3(t_env *env, t_node *node)
{
	if (node->command && !ft_strcmp(node->command, "exit"))
	{
		ft_exit(node, env);
		if (env->n_pipes > 0)
			exit(0);
		return (1);
	}
	return (0);
}

void	ft_execve_p2(t_env *env, t_node *node)
{
	int	pid;

	if (ft_execve_buildin_1(env, node) == 1)
		return ;
	else if (ft_execve_buildin_2(env, node) == 1)
		return ;
	else if (ft_execve_buildin_3(env, node) == 1)
		return ;
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(node->path_command, node->exec_args, env->envp) == -1)
			{
				ft_error_cmd_fail(node->command);
				exit(0);
			}
		}
		waitpid(0, 0, 0);
	}
}

void	ft_execve(t_env *env, t_node *node)
{
	if (env->n_pipes > 0)
	{
		ft_execve_buildin_1(env, node);
		ft_execve_buildin_2(env, node);
		ft_execve_buildin_3(env, node);
		if (execve(node->path_command, node->exec_args, env->envp) == -1)
		{
			printf("%s: command not found\n", node->command);
			exit(0);
		}
		if (env->n_pipes > 0)
			exit(0);
	}
	else
	{
		if (ft_execve_buildin_1(env, node) == 1)
			return ;
		else if (ft_execve_buildin_2(env, node) == 1)
			return ;
		else if (ft_execve_buildin_3(env, node) == 1)
			return ;
		else
			ft_execve_p2(env, node);
	}
}
