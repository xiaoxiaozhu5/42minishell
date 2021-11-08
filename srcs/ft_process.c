#include "ft_minishell.h"

void	ft_process(t_env *env)
{
	(void)env;
	if (env->cmds->command && !ft_strncmp(env->cmds->command, "export", ft_strlen(env->cmds->command)))
		ft_export(env->cmds, env);
	if (env->cmds->command && !ft_strncmp(env->cmds->command, "unset", ft_strlen(env->cmds->command)))
		ft_unset(env->cmds, env);
}
