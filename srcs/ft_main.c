/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:25:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/27 14:53:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_destroy_env(t_env *env)
{
	ft_clear_cmds(env);
	ft_strsfree(env->envp);
	free(env);
}

t_env	*ft_init_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->envp = ft_strscopy(envp);
	env->cmds = 0;
	env->last_status = 0;
	env->n_pipes = 0;
	return (env);
}

void	ft_initter(t_env **env, char **envp, char **input)
{
	*env = ft_init_env(envp);
	ft_init_history();
	*input = 0;
}

void	ft_readline(char **input, t_env *env)
{
	*input = readline("42minishell $> ");
	if (!*input)
	{
		ft_putendl_fd("exit", 1);
		ft_clear_cmds(env);
		ft_destroy_env(env);
		exit(1);
	}
	ft_add_history(*input);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env;

	(void)argc;
	(void)argv;
	ft_initter(&env, envp, &input);
	while (1)
	{
		ft_init_signals();
		ft_readline(&input, env);
		if (ft_preparser(input) == 0)
		{
			input = ft_rm_whitespace(input);
			input = ft_parser(input, env);
			ft_build_cmds(&env->cmds, input);
			ft_preprocess(env);
			ft_process(env);
			ft_clear_cmds(env);
			ft_strsfree(env->execve_paths);
		}
		free(input);
	}
}
