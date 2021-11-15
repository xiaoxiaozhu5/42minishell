#include "ft_minishell.h"

void	ft_pwd(t_env *env)
{
	char	*result;

	result = ft_get_value("PWD", env->envp);
	printf("%s\n", result);
	free(result);
	env->last_status = 0;
}
