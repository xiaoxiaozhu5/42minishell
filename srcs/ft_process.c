#include "ft_minishell.h"

char	*find_path12(t_env *env)
{
	char	*str;
	int		i;

	i = 0;
	while (ft_strncmp(env->envp[i], "PWD", 3) != 0)
	{
		i++;
	}
	str = ft_strjoin(env->envp[i] + 4, "/");
	return (str);
}

void	ft_process(t_env *env)
{
	t_node *to_modify;

	if (!env->cmds->command)
		return ;
	to_modify = env->cmds;
	while (to_modify != NULL)
	{
		to_modify->path_command = find_path1(env, to_modify);
		if (to_modify->path_command == NULL)
		{
			to_modify->path_command = find_path12(env);
			to_modify->path_command = ft_strjoin(to_modify->path_command, to_modify->command);
		}
		to_modify = (t_node *)to_modify->next;
	}
	to_modify = env->cmds;
	if (env->cmds->command != NULL && env->n_pipes > 0)
	{
		ft_new_pipe(env);
	}
	else
		make_redirrect(to_modify, env);
	waitpid(0, 0, 0);
}
