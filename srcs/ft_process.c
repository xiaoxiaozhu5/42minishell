#include "ft_minishell.h"

void	ft_process(t_env *env)
{
	// printf("n pipes %d\n", env->n_pipes);
	t_node *to_modify;

	to_modify = env->cmds;
	while (to_modify != NULL)
	{
		to_modify->path_command = find_path1(env, to_modify);
		to_modify = (t_node *)to_modify->next;
	}
	to_modify = env->cmds;
	if (env->cmds->command != NULL && env->n_pipes > 0)
	{
		// pid = fork();
		// if (pid == 0)
			ft_new_pipe(env);
		// waitpid(0,0,0);
	}
	else
	{
		make_redirrect(to_modify, env);
	}
	waitpid(0, 0, 0);
	// sleep(10);
}
