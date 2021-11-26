/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:25:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/27 14:53:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**ft_exec_args_end(t_node *node)
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

void	ft_exec_args(t_node *node)
{
	char	**command;
	char	**new_args;
	char	**end;

	end = ft_exec_args_end(node);
	if (node->command)
	{
		command = ft_strscreate(node->command);
		if (end)
		{
			new_args = ft_strsjoin(command, end);
			ft_strsfree(command);
			ft_strsfree(end);
			node->exec_args = new_args;
		}
		else
			node->exec_args = command;
	}
}
