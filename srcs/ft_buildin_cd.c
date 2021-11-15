#include "ft_minishell.h"

void	ft_update_pwd(t_env *env, char *path)
{
	char	*pwd;
	char	*temp;
	char	*temp2;
	char	buffer[2048];
	char	*error_msg;

	pwd = getcwd(buffer, 2048);
	temp = ft_strjoin("OLDPWD", "=");
	temp2 = ft_strjoin(temp, pwd);
	free(temp);
	if (chdir(path) != 0 && ft_strchr(path, '>') == NULL)
	{
		error_msg = ft_strjoin("cd: ", path);
		ft_strerror(error_msg, strerror(errno));
		free(error_msg);
		return ;
	}
	ft_envp_add(&(env->envp), temp2);
	free(temp2);
	pwd = getcwd(buffer, 2048);
	temp = ft_strjoin("PWD", "=");
	temp2 = ft_strjoin(temp, pwd);
	free(temp);
	ft_envp_add(&(env->envp), temp2);
	free(temp2);
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
	ft_update_pwd(env, path);
	free(path);
}

void	ft_cd(t_node *node, t_env *env)
{
	char	*path;

	if ((!node->args[1]) || ft_strcmp(node->args[1], "~") == 0)
	{
		ft_set_home(env);
		return ;
	}
	else if (ft_strcmp(node->args[1], "-") == 0)
	{
		path = ft_get_value("OLDPWD", env->envp);
		ft_update_pwd(env, path);
		free(path);
	}
	else
		ft_update_pwd(env, node->args[1]);
}
