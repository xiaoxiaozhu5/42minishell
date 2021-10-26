#include "ft_minishell.h"

// Для теста парсера:
// comma'n\nn'dd000\'00co"mm\""an'dddd'a
// Результат должен быть:
// comman\nndd000'00comm"andddda

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = malloc(sizeof(t_env));
	ft_init_history();
	char *res = ft_rm_whitespace(ft_strdup("     Hello                   'world!'            "));
	printf("new: [%s]\n", res);
	free(res);
	exit(1);
	while (1)
	{
		input = readline("42minishell:~$ ");
		ft_add_history(input);
		if (ft_preparser(input) == 0)
		{
			input = ft_parser(input, env, envp);
			ft_build_cmds(env, input);
			ft_process(env);
		}
		free(input);
	}
	free(env);
	// TODO free(env->cmds);
	// TODO bug echo '$USER' "'$USER'"
	// TODO if no leaks (remove -g)
}
