/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:25:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/27 14:53:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*find_path12(t_env *env)
{
	char	*str;
	char	*temp;

	temp = ft_get_value("PWD", env->envp);
	str = ft_strjoin(temp, "/");
	free(temp);
	return (str);
}

void	ft_modify(t_env *env, t_node *to_modify)
{
	char	*temp_str;

	while (to_modify != NULL)
	{
		to_modify->path_command = find_path1(env, to_modify);
		if (to_modify->path_command == NULL)
		{
			temp_str = find_path12(env);
			to_modify->path_command = ft_strjoin(temp_str, to_modify->command);
			free(temp_str);
		}
		to_modify = (t_node *)to_modify->next;
	}
}

void	no_newline_for_sigquit(int sig)
{
	if (sig == SIGUSR1)
		signal(SIGQUIT, SIG_IGN);
}

void	ft_process(t_env *env)
{
	t_node	*to_modify;

	signal(SIGUSR1, no_newline_for_sigquit);
	if (!env->cmds->command)
		return ;
	to_modify = env->cmds;
	ft_modify(env, to_modify);
	if (env->cmds->command != NULL && env->n_pipes > 0)
		ft_new_pipe(env);
	else
		make_redirrect(to_modify, env);
	waitpid(0, 0, 0);
}
