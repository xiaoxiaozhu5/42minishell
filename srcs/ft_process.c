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
	if (env->cmds->command && !ft_strcmp(env->cmds->command, "echo"))
		ft_echo(env->cmds, env);
	if (env->cmds->command && !ft_strcmp(env->cmds->command, "env"))
		ft_env(env);
	if (env->cmds->command && !ft_strcmp(env->cmds->command, "exit"))
		ft_exit(env);

	// printf("n pipes %d\n", env->n_pipes);


	// if (env->cmds->command != NULL && env->n_pipes > 0)
		// ft_new_pipe(env);

	// t_redir *redir;
	// char *cmd;

	// cmd = ft_strdup(find_path1(env, env->cmds));
	// redir = (t_redir *)env->cmds->redirs;
	// make_redirrect(env->cmds);
	// int pid;
	// pid = fork();
	// if (pid == 0)
	// {
	// 	execve(cmd, env->cmds->exec_args, env->envp);
	// }
	// waitpid(0, 0, 0);
}
