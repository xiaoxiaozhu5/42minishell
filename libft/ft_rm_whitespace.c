/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:37 by kricky            #+#    #+#             */
/*   Updated: 2021/11/12 11:26:57 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_skip_quotes(const char *input, int *i, const char c)
{
	(*i)++;
	while (input[*i] != c && input[*i] != '\0')
		(*i)++;
	(*i)++;
}

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
	{
		*i = start;
		return (input);
	}
	if (start == 0)
		tmp1 = ft_substr(input, 0, start);
	else
		tmp1 = ft_substr(input, 0, start + 1);
	tmp2 = ft_strdup(input + *i);
	tmp3 = ft_strjoin(tmp1, tmp2);
	if (tmp3[ft_strlen(tmp3) - 1] == ' ')
		tmp3[ft_strlen(tmp3) - 1] = '\0';
	free(tmp1);
	free(tmp2);
	free(input);
	*i = start;
	return (tmp3);
}

char	*ft_rm_whitespace(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		while (input[i] == '\'')
			ft_skip_quotes(input, &i, '\'');
		while (input[i] == '\"')
			ft_skip_quotes(input, &i, '\"');
		if (input[i] && (input[i] == ' ' || input[i] == '\t'))
			input = ft_rm_spaces(input, &i);
		i++;
	}
	return (input);
}
