#include "ft_minishell.h"

void	ft_destroy_env(t_env *env)
{
	ft_strsfree(env->envp);
	free(env->username);
	free(env);
}

t_env	*ft_init_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->envp = ft_strscopy(envp);
	env->cmds = 0;
	env->last_status = 0;
	env->username = ft_get_value("USER", envp);
	return (env);
}

void	ft_sigint(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_initter(t_env **env, char **envp, char **input)
{
	*env = ft_init_env(envp);
	ft_init_history();
	signal(SIGINT, ft_sigint);
	*input = 0;
}

void ft_readline(char **input, t_env *env)
{
	*input = readline("42minishell:~$ ");
	if (!*input)
	{
		ft_putchar_fd('\n', 1);
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
		ft_readline(&input, env);
		if (ft_preparser(input) == 0)
		{
			input = ft_rm_whitespace(input);
			printf("Formatted: [%s]\n", input);
			input = ft_parser(input, env);
			printf("Parser: [%s]\n", input);
			ft_build_cmds(&env->cmds, input);
			ft_list_print(&env->cmds);
			ft_process(env);
			ft_clear_cmds(env);
		}
		free(input);
	}
	ft_destroy_env(env);
	// TODO remove -g
}
