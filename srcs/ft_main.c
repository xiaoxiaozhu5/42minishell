#include "ft_minishell.h"

int	main(void)
{
	char	*input;
	t_env	*env;

	ft_init_history();
	while (1)
	{
		input = readline("\033[0;34m42minishell\033[0m: ");
		ft_add_history(input);
		env = ft_parser(input);
		if (env)
			ft_process(env);
		free(env);
	}
}
