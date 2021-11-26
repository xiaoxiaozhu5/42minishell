/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:12:57 by faggar            #+#    #+#             */
/*   Updated: 2021/11/26 17:45:50 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	double_left(t_redir *redir)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		redir_sig();
		make_heredeock(redir);
		exit(0);
	}
	waitpid(0, 0, 0);
	exit(0);
	return (1);
}

static void	choose_redirrect(t_redir *redirs, t_node *cmd)
{
	if (redirs->type == REDIRECT_RIGHT)
	{
		simple_right(redirs, cmd);
	}
	else if (redirs->type == REDIRECT_DOUBLE_RIGHT)
	{
		double_right(redirs, cmd);
	}
	else if (redirs->type == REDIRECT_LEFT)
	{
		if (simple_left(redirs, cmd) == -1)
		{
			exit(0);
		}
	}
}

static int	check_redirs(t_node *cur_cmd, t_redir	*redirs)
{
	check_heredock(redirs);
	redirs = (t_redir *)cur_cmd->redirs;
	while (redirs != NULL)
	{
		if (redirs->value[0] == '\0')
		{
			printf("error!\n");
			if (cur_cmd->next == NULL)
				return (-1);
			exit (-1);
		}
		redirs = (t_redir *)redirs->next;
	}
	return (0);
}

static void	all_redir_things(t_node *cur_cmd, t_env *env)
{
	t_redir	*redirs;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		redirs = (t_redir *)cur_cmd->redirs;
		while (redirs != NULL)
		{
			choose_redirrect(redirs, cur_cmd);
			redirs = (t_redir *)redirs->next;
		}
		ft_execve(env, cur_cmd);
		exit(0);
	}
	waitpid(0, 0, 0);
	if (env->n_pipes > 0)
		exit(0);
}

void	make_redirrect(t_node *cur_cmd, t_env *env)
{
	t_redir	*redirs;

	redirs = (t_redir *)cur_cmd->redirs;
	if (check_redirs(cur_cmd, redirs) == -1)
		return ;
	redirs = (t_redir *)cur_cmd->redirs;
	cur_cmd->fds[1] = 2;
	cur_cmd->fds[1] = dup(cur_cmd->redir_1);
	if (cur_cmd->redirs != NULL)
	{
		all_redir_things(cur_cmd, env);
	}
	else
		ft_execve(env, cur_cmd);
}
