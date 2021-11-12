#include "ft_minishell.h"

void	ft_update_pwd(t_env *env)
{
	char	*pwd;
	char	*temp;
	char	*temp2;
	char	buffer[2048];


//	if (chdir(path) != 0 && ft_strchr(path, '>') == NULL)
//	{
//		error_msg = ft_strjoin("cd: ", path);
//		error_message(error_msg, strerror(errno), 1);
//		free(error_msg);
//		return ;
//	}
	pwd = getcwd(buffer, 2048);
	temp = ft_strjoin("PWD", "=");
	temp2 = ft_strjoin(temp, pwd);
	free(temp);
	ft_envp_add(&(env->envp), temp2);
	free(temp2);
}

void	ft_change_directory(t_env *env, char *path)
{
	if (chdir(path) == 0)
		ft_update_pwd(env);
}

void	ft_set_home(t_env *env)
{
	char	*path;

	path = ft_get_value("HOME", env->envp);
	if (path == NULL)
	{
		ft_error_homeless("cd");
		free(path);
		return ;
	}
	ft_change_directory(env, path);
	free(path);
}

void	ft_cd(t_node *node, t_env *env)
{
	char	*arg;

	(void)env;
	if (node->args)
	{
		arg = node->args[0];
		ft_change_directory(env, arg);
	}
}
