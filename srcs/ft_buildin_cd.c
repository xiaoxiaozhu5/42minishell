/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:25:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/27 14:53:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_strerror_free(char *error_msg1, const char *error_msg2)
{
	printf("%s: ", SHELL_NAME);
	printf("%s: ", error_msg1);
	printf("%s\n", error_msg2);
	free(error_msg1);
}

int	ft_update_pwd(t_env *env, char *path)
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
		ft_strerror_free(error_msg, strerror(errno));
		return (1);
	}
	ft_envp_add(&(env->envp), temp2);
	free(temp2);
	pwd = getcwd(buffer, 2048);
	temp = ft_strjoin("PWD", "=");
	temp2 = ft_strjoin(temp, pwd);
	free(temp);
	ft_envp_add(&(env->envp), temp2);
	free(temp2);
	return (0);
}

int	ft_set_home(t_env *env)
{
	char	*path;

	path = ft_get_value("HOME", env->envp);
	if (path == NULL)
	{
		ft_error_homeless("cd");
		free(path);
		return (1);
	}
	ft_update_pwd(env, path);
	free(path);
	return (0);
}

void	ft_cd(t_node *node, t_env *env)
{
	char	*path;

	if (!node->args || ft_strcmp(node->args[0], "~") == 0)
	{
		env->last_status = ft_set_home(env);
		return ;
	}
	else if (ft_strcmp(node->args[0], "-") == 0)
	{
		path = ft_get_value("OLDPWD", env->envp);
		env->last_status = ft_update_pwd(env, path);
		free(path);
	}
	else
		env->last_status = ft_update_pwd(env, node->args[0]);
}
