/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:25:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/27 14:53:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static void	ft_free(char *str1, char *str2)
{
	free(str1);
	free(str2);
}

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
	ft_free(tmp1, tmp2);
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
