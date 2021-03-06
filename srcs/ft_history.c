/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:25:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/27 14:53:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_history_old_fill(int fd)
{
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		add_history(line);
		free(line);
	}
	free(line);
}

void	ft_add_history(char *line)
{
	int	history_file;

	if (!line)
		return ;
	if (*line != '\0')
	{
		add_history(line);
		history_file = open(".history", O_APPEND | O_WRONLY);
		ft_putendl_fd(line, history_file);
		close(history_file);
	}
}

void	ft_init_history(void)
{
	int	history_file;

	history_file = open(".history", O_RDWR | O_CREAT, 0666);
	if (history_file != -1)
		ft_history_old_fill(history_file);
	close(history_file);
}
