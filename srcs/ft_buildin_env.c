/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:25:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/27 14:53:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strchr(env->envp[i], '=')
			&& *(ft_strchr(env->envp[i], '=') + 1) != '\0')
			printf("%s\n", env->envp[i]);
		i++;
	}
}
