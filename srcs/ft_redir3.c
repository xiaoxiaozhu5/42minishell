/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:46:25 by faggar            #+#    #+#             */
/*   Updated: 2021/11/26 17:46:58 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	redir_sig(void)
{
	signal(SIGINT, sigint_r);
	signal(SIGQUIT, sigquit_r);
	kill(0, SIGUSR1);
}

void	check_heredock(t_redir *redirs)
{
	int	pid;

	while (redirs != NULL)
	{
		if (redirs->type == REDIRECT_DOUBLE_LEFT)
		{
			pid = fork();
			if (pid == 0)
				double_left(redirs);
			waitpid(0, 0, 0);
		}
		redirs = (t_redir *)redirs->next;
	}
}

void	make_heredeock(t_redir *redir)
{
	char	*heredock;

	while (1)
	{
		heredock = readline("heredock> ");
		if (!heredock)
		{
			printf("heredock> %s\n", redir->value);
			exit(0);
		}
		if ((ft_strcmp(heredock, redir->value)) == 0)
		{
			free(heredock);
			break ;
		}
		else
			free(heredock);
	}
}
