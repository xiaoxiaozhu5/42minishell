#include "ft_minishell.h"

char	*find_path12(t_env *env)
{
	char	*str;
	char	*temp;

	temp = ft_get_value("PWD", env->envp);
	str = ft_strjoin(temp, "/");
	free(temp);
	return (str);
}

void	ft_modify(t_env *env, t_node *to_modify)
{
	char	*temp_str;

	while (to_modify != NULL)
	{
		to_modify->path_command = find_path1(env, to_modify);
		if (to_modify->path_command == NULL)
		{
			temp_str = find_path12(env);
			to_modify->path_command = ft_strjoin(temp_str, to_modify->command);
			free(temp_str);
		}
		to_modify = (t_node *)to_modify->next;
	}
}

void	ft_process(t_env *env)
{
	t_node *to_modify;

	if (!env->cmds->command)
		return ;
	to_modify = env->cmds;
	ft_modify(env, to_modify);
	if (env->cmds->command != NULL && env->n_pipes > 0)
		ft_new_pipe(env);
	else
		make_redirrect(to_modify, env);
	waitpid(0, 0, 0);
}
