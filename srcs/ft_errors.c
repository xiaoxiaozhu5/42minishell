/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:25:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/27 14:53:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_error_unexpected_token(const char token)
{
	if (token)
	{
		printf("%s: ", SHELL_NAME);
		printf("%s ", ERROR_UNEXPECTED_TOKEN);
		printf("`%c`\n", token);
	}
	return (token);
}

void	ft_error_cmd_fail(const char *cmd_name)
{
	printf("%s: ", SHELL_NAME);
	printf("%s: ", cmd_name);
	printf("%s\n", ERROR_CMD_NOT_FOUND);
}

void	ft_error_identifier(const char *cmd_name, const char identifier)
{
	printf("%s: ", SHELL_NAME);
	printf("%s: ", cmd_name);
	printf("'%c': ", identifier);
	printf("%s\n", ERROR_IDENTIFIER);
}

void	ft_error_homeless(const char *cmd_name)
{
	printf("%s: ", SHELL_NAME);
	printf("%s: ", cmd_name);
	printf("%s\n", ERROR_HOMELESS);
}
