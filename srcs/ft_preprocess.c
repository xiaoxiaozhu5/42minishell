/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:25:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/27 14:53:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_pipes_counter(t_env *env)
{
	t_node	*iter;

	iter = env->cmds;
	while (iter)
	{
		if (iter->c_end == '|')
			env->n_pipes++;
		iter = iter->next;
	}
}

char	**ft_get_execve_paths(char **envp)
{
	char	**result;
	char	*paths;

	paths = ft_get_value("PATH", envp);
	result = ft_split(paths, ':');
	free(paths);
	return (result);
}

void	ft_preprocess(t_env *env)
{
	ft_pipes_counter(env);
	env->execve_paths = ft_get_execve_paths(env->envp);
}
