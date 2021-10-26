/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:37 by kricky            #+#    #+#             */
/*   Updated: 2021/10/26 14:44:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_in_ignore(const char *str, int i, const char c)
{
	int	j;
	int	left_check;
	int	right_check;

	j = i;
	left_check = 0;
	right_check = 0;
	while (i != -1 && !left_check)
	{
		if (str[i] == c)
			left_check = 1;
		i--;
	}
	i = j;
	while (str[i] != '\0' && !right_check)
	{
		if (str[i] == c)
			right_check = 1;
		i++;
	}
	return (left_check && right_check);
}

void	ft_rm_spaces(char **input, int *i)
{
	int		start;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	start = *i;
	*input = *input;
	while ((*input)[*i] && (*input)[*i] == ' ' || && (*input)[*i] == '\t')
	{
		(*i)++;
	}
	if (*i - start < 2)
		return ;
	printf("start: %d, end: %d\n", start, *i);
	tmp1 = ft_substr(*input, 0, start);
	tmp2 = ft_strdup(*input + *i);
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	free(*input);
	*input = tmp3;
}

void	ft_rm_whitespace(char **input, const char *ignore_set)
{
	int		i;
	char	*str;

	(void)ignore_set;
	i = 0;
	str = *input;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t')
			&& !(ft_in_ignore(*input, i, '\'')
				|| ft_in_ignore(*input, i, '\"')))
			ft_rm_spaces(input, &i);
		i++;
	}
}
