#include "ft_minishell.h"

// Для теста парсера:
// comma'n\nn'dd000\'00co"mm\""an'dddd'a
// Результат должен быть:
// comman\nndd000'00comm"andddda

int	main(void)
{
	char	*input;
	t_env	*env;

	env = malloc(sizeof(t_env));
	ft_init_history();
	while (1)
	{
		input = readline("\033[0;34m42minishell\033[0m: ");
		ft_add_history(input);
		if (ft_preparser(input) == 0)
		{
			input = ft_parser(input);
			ft_process(env);
		}
		free(input);
	}
	free(env);
}
