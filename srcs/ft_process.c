#include "ft_minishell.h"

void	ft_process(t_env *env)
{
	(void)env;
	if (env->cmds->command && !ft_strcmp(env->cmds->command, "export"))
		ft_export(env->cmds, env);
	if (env->cmds->command && !ft_strcmp(env->cmds->command, "unset"))
		ft_unset(env->cmds, env);
}
