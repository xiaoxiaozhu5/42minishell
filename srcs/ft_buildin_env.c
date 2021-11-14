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
