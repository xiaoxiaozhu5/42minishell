#include "ft_minishell.h"

void	ft_process(t_env *env)
{
	(void)env;
	printf("Функция работающая после парсера\n");
	if (env->cmds->command && !ft_strncmp(env->cmds->command, "export", ft_strlen(env->cmds->command)))
		ft_export(env->cmds, env);
}
