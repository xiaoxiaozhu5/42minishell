#include "ft_minishell.h"

void	ft_destroy_env(t_env *env)
{
	ft_clear_cmds(env);
	ft_strsfree(env->envp);
	ft_strsfree(env->execve_paths);
	free(env);
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

t_env	*ft_init_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->envp = ft_strscopy(envp);
	env->cmds = 0;
	env->last_status = 0;
	env->execve_paths = ft_get_execve_paths(envp);
	env->n_pipes = 0;
	return (env);
}

void	ft_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_initter(t_env **env, char **envp, char **input)
{
	*env = ft_init_env(envp);
	ft_init_history();
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	*input = 0;
}

void ft_readline(char **input, t_env *env)
{
	*input = readline("\001\033[1;91m\00242minishell $>\001\033[0m\002 ");
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
		ft_readline(&input, env);
		if (ft_preparser(input) == 0)
		{
			input = ft_rm_whitespace(input);
			// printf("Formatted: [%s]\n", input);
			input = ft_parser(input, env);
			// printf("Parser: [%s]\n", input);
			ft_build_cmds(&env->cmds, input);
			// ft_list_print(&env->cmds);
			ft_preprocess(env);
			ft_process(env);
			ft_clear_cmds(env);
		}
		free(input);
	}
	ft_destroy_env(env);
	// TODO remove -g
}
