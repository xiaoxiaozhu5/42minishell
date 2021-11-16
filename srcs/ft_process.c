#include "ft_minishell.h"

void	ft_process(t_env *env)
{
	// if (env->cmds->command != NULL && env->n_pipes > 0)
		ft_new_pipe(env);

	t_redir *redir;
	char *cmd;

	cmd = ft_strdup(find_path1(env, env->cmds));
	redir = (t_redir *)env->cmds->redirs;
	int pid;
	pid = fork();
	if (pid == 0)
	{
		make_redirrect(env->cmds);
		execve(cmd, env->cmds->exec_args, env->envp);
	}
	waitpid(0, 0, 0);
	// dup2(env->cmds->fds[0], env->cmds->redir_0);
	// dup2(env->cmds->fds[1], env->cmds->redir_1);
	// dup2(0, env->cmds->redir_0);
	// close(env->cmds->redir_1);
	printf("%d	%d\n",env->cmds->redir_1, env->cmds->redir_0);
	// close(env->cmds->redir_0);
	// dup2(1, env->cmds->redir_1);
	// dup2(0,env->cmds->redir_0);	
}
