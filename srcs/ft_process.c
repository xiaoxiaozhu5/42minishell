#include "ft_minishell.h"

void	ft_process(t_env *env)
{
	(void)env;
	if (env->cmds->command && !ft_strcmp(env->cmds->command, "export"))
		ft_export(env->cmds, env);
	if (env->cmds->command && !ft_strcmp(env->cmds->command, "unset"))
		ft_unset(env->cmds, env);
	if (env->cmds->command && !ft_strcmp(env->cmds->command, "pwd"))
		ft_pwd(env);
	if (env->cmds->command && !ft_strcmp(env->cmds->command, "cd"))
		ft_cd(env->cmds, env);

	// printf("n pipes %d\n", env->n_pipes);
	 ft_new_pipe(env);
	// t_node *iter;
	if (env->cmds->command != NULL)
		ft_new_pipe(env);
	// iter = env->cmds;
	// while (iter)
	// {
	// 	printf("%s\n", iter->command);
	// 	printf("%c\n", iter->c_end);
	// 	iter = iter->next;
	// }
}
