#include "ft_minishell.h"

void	ft_update_path(t_env *env)
{
	char	*pwd;
	char	*temp;
	char	*temp2;
	char	buffer[2048];

	pwd = getcwd(buffer, 2048);
	temp = ft_strjoin("PWD", "=");
	temp2 = ft_strjoin(temp, pwd);
	free(temp);
	ft_envp_add(&(env->envp), temp2);
	free(temp2);
}

void	ft_cd(t_node *node, t_env *env)
{
	char	*arg;

	(void)env;
	if (node->args)
	{
		arg = node->args[0];
		if (chdir(arg) == 0)
			ft_update_path(env);
	}
}
