#include "ft_minishell.h"

// Для теста парсера:
// comma'n\nn'dd000\'00co"mm\""an'dddd'a
// Результат должен быть:
// comman\nndd000'00comm"andddda

void	ft_destroy_env(t_env *env)
{
	free(env);
}

t_env	*ft_init_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->envp = envp;
	env->last_status = 0;
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = ft_init_env(envp);
	ft_init_history();
//	char *str = ft_rm_whitespace(ft_strdup("hello            world   jsad sadj asj dksajd aks d         sadsa"));
//	printf("res: [%s]\n", str);
//	exit(1);
	while (1)
	{
		input = readline("42minishell:~$ ");
		ft_add_history(input);
		if (ft_preparser(input) == 0)
		{
			input = ft_rm_whitespace(input);
			printf("Отформатировано: [%s]\n", input);
			input = ft_parser(input, env);
			printf("Спарсилось как: [%s]\n", input);
			//ft_build_cmds(env, input);
			ft_process(env);
		}
		free(input);
	}
	ft_destroy_env(env);
	// TODO free(env->cmds);
	// TODO bug echo '$USER' "'$USER'"
	// TODO if no leaks (remove -g)
}
