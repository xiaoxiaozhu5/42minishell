#include "ft_minishell.h"

void	ft_destroy_env(t_env *env)
{
	free(env->username);
	free(env);
}

t_env	*ft_init_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->envp = envp;
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = ft_init_env(envp);
	ft_init_history();
	signal(SIGINT, ft_sigint);
	input = 0;
	while (1)
	{
		input = readline("42minishell:~$ ");
		if (!input)
		{
			ft_putchar_fd('\n', 1);
			ft_clear_cmds(env);
			ft_destroy_env(env);
			exit(1);
		}
		ft_add_history(input);
		if (ft_preparser(input) == 0)
		{
			input = ft_rm_whitespace(input);
			printf("Formatted: [%s]\n", input);
			input = ft_parser(input, env);
			printf("Parser: [%s]\n", input);
			ft_build_cmds(&env->cmds, input);
			ft_list_print(&env->cmds);
			ft_clear_cmds(env);
			ft_process(env);
		}
		free(input);
	}
	ft_destroy_env(env);
	// TODO remove -g
}
