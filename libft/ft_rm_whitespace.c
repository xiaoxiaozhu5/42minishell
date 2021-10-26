/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:37 by kricky            #+#    #+#             */
/*   Updated: 2021/10/26 17:54:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*ft_rm_spaces(char *input, int *i)
{
	int		start;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	start = *i;
	while (input[*i] != '\0' && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
	if (*i - start < 2)
		return (input);
	tmp1 = ft_substr(input, 0, start);
	tmp2 = ft_strdup(input + *i);
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	free(input);
	return (tmp3);
}

char	*ft_rm_whitespace(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			while (input[i] != '\'')
				i++;
			i++;
		}
		if (input[i] == '\"')
		{
			while (input[i] != '\"')
				i++;
			i++;
		}
		if (input[i] && (input[i] == ' ' || input[i] == '\t'))
		{
			input = ft_rm_spaces(input, &i);
		}
		i++;
	}
	return (input);
}
