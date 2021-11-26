/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:25:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/27 14:53:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_clear_redirs(t_redir **lst)
{
	t_redir	*next_ptr;
	t_redir	*iter;

	iter = *lst;
	while (iter)
	{
		next_ptr = iter->next;
		free(iter->value);
		free(iter);
		iter = next_ptr;
	}
	*lst = 0;
}

void	ft_clear_nodes(t_node **lst)
{
	t_node	*iter;
	t_node	*temp;

	temp = *lst;
	while (temp)
	{
		iter = temp->next;
		if (temp->redirs)
			ft_clear_redirs((t_redir **)&(temp->redirs));
		if (temp->command)
			free(temp->command);
		if (temp->flags)
			ft_strsfree(temp->flags);
		if (temp->exec_args)
			ft_strsfree(temp->exec_args);
		if (temp->args)
			ft_strsfree(temp->args);
		if (temp->path_command)
			free(temp->path_command);
		free(temp);
		temp = iter;
	}
	*lst = 0;
}

void	ft_clear_cmds(t_env *env)
{
	ft_clear_nodes(&env->cmds);
	env->cmds = 0;
	env->n_pipes = 0;
}
