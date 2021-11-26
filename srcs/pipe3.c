/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:41:22 by faggar            #+#    #+#             */
/*   Updated: 2021/11/26 16:41:23 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*find_path1(t_env *data, t_node *iter)
{
	struct stat	buff;
	char		*needed_cmd;
	int			i;
	int			res;
	char		*temp_str;

	i = 0;
	needed_cmd = ft_strdup(iter->command);
	res = stat(needed_cmd, &buff);
	if (res == 0 && (buff.st_mode))
		return (needed_cmd);
	while (data->execve_paths[i])
	{
		temp_str = ft_strjoin(data->execve_paths[i], "/");
		needed_cmd = ft_strjoin(temp_str, iter->command);
		free(temp_str);
		res = stat(needed_cmd, &buff);
		if (res == 0 && (buff.st_mode))
			return (needed_cmd);
		free(needed_cmd);
		temp_str = NULL;
		i++;
	}
	return (NULL);
}

static int	**allocate_ar_of_fds_and_pid(int n_pipes, int **pid)
{
	int	**fds;
	int	i;

	i = 0;
	fds = malloc(sizeof(int *) * (n_pipes + 1));
	if (!fds)
		return (NULL);
	while (i < n_pipes)
	{
		fds[i] = (int *) malloc(sizeof (int) * 2);
		if (!fds[i])
			return (NULL);
		pipe(fds[i]);
		i++;
	}
	fds[i] = (int *) malloc(sizeof (int) * 2);
	pipe(fds[i]);
	*pid = (int *)malloc(sizeof(int) * (n_pipes + 1));
	return (fds);
}

static void	close_open_things(t_lol *kek, int pipes)
{
	if (kek->pid[kek->i] == 0 && kek->i == 0)
	{
		close(kek->p[kek->i][0]);
		dup2(kek->p[kek->i][1], 1);
	}
	else if (kek->i != pipes)
	{
		close(kek->p[kek->i - 1][1]);
		dup2(kek->p[kek->i - 1][0], 0);
		close(kek->p[kek->i][0]);
		dup2(kek->p[kek->i][1], 1);
	}
	else if (kek->i == pipes)
	{
		close(kek->p[kek->i - 1][1]);
		dup2(kek->p[kek->i - 1][0], 0);
	}
}

static void	pipe_v2(t_lol *kek, t_env *data, t_node *iter)
{
	if (kek->pid[kek->i] > 0)
	{
		close(kek->p[kek->i][1]);
	}
	else if (kek->pid[kek->i] == 0)
	{	
		if (iter->redirs != NULL)
		{
			make_redirrect(iter, data);
		}
		else
		{
			close_open_things(kek, data->n_pipes);
			ft_execve(data, iter);
		}
	}
}

void	ft_new_pipe(t_env *data)
{
	t_node	*iter;
	t_lol	kek;

	kek.p = allocate_ar_of_fds_and_pid(data->n_pipes, &kek.pid);
	iter = data->cmds;
	kek.i = 0;
	while (kek.i <= data->n_pipes)
	{
		kek.pid[kek.i] = fork();
		pipe_v2(&kek, data, iter);
		iter = iter->next;
		kek.i++;
	}
	while (kek.i--)
		waitpid(0, 0, 0);
	free(kek.pid);
	kek.i = -1;
	while (++kek.i <= data->n_pipes)
		free(kek.p[kek.i]);
	free(kek.p);
}
