/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:14 by kricky            #+#    #+#             */
/*   Updated: 2021/10/21 16:20:13 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_clear_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}

static int	ft_substr_strlen(char const *s, int start, char end)
{
	int	i;
	int	counter;

	i = start;
	counter = 0;
	while (s[i] != '\0' && s[i] != end)
	{
		i++;
		counter++;
	}
	return (counter);
}

static	int	ft_nbrstrs(char const *s, char c)
{
	int	i;
	int	counter;
	int	substr_start;

	i = 0;
	counter = 0;
	substr_start = -1;
	while (s[i] != '\0')
	{
		if (s[i] != c && substr_start == -1)
		{
			substr_start = 1;
			counter++;
		}
		if (s[i] == c && substr_start != -1)
			substr_start = -1;
		i++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		substr_start;
	char	**strs;

	i = 0;
	j = 0;
	substr_start = -1;
	strs = 0;
	if (s)
		strs = ft_calloc((ft_nbrstrs(s, c) + 1), sizeof(char *));
	while (strs && s[i] != '\0')
	{
		if (s[i] != c && substr_start == -1)
		{
			substr_start = 1;
			strs[j] = ft_substr(s, i, ft_substr_strlen(s, i, c));
			if (!strs[j++])
				return (ft_clear_strs(strs));
		}
		if (s[i++] == c && substr_start != -1)
			substr_start = -1;
	}
	return (strs);
}
