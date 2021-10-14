/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                  :+:      :+:    :+:   	  */
/*                                                    +:+ +:+         +:+     */
/*   By:  <kricky@student.21-school.ru>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:15:31 by                   #+#    #+#             */
/*   Updated: 2021/10/14 16:17:36 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// Constants
# define ERROR "Error!\n"

// Typedefs

// Structures
typedef struct s_env
{
	int	def;
}	t_env;

// History
void	ft_init_history();
void	ft_add_history(char *line);

// Parser
t_env	*ft_parser(const char *input);

// Process
void	ft_process(t_env *env);

#endif