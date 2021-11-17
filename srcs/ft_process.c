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
	if (env->cmds->command != NULL && env->n_pipes > 0)
		ft_new_pipe(env);
	// if (env->cmds->command != NULL && env->cmds->redirs != NULL)
	// {
	// 	make_redirrect(env->cmds, env);
	// }
	// sleep(10);
	// else
	// {

	// }

	// t_redir *redir;
	// char *cmd;

	// cmd = ft_strdup(find_path1(env, env->cmds));
	// redir = (t_redir *)env->cmds->redirs;
	// int pid;
	// pid = fork();
	// if (pid == 0)
	// {
	// 	make_redirrect(env->cmds, env);
	// 	execve(cmd, env->cmds->exec_args, env->envp);
	// }
	waitpid(0, 0, 0);
	// sleep(10);
}
