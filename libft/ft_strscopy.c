/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscopy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:28 by kricky            #+#    #+#             */
/*   Updated: 2021/11/07 18:33:09 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strscopy_append(char **strs, const char *str)
{
	int		strs_n;
	int		i;
	char	**result;

	strs_n = 0;
	while (strs[strs_n])
		strs_n++;
	result = malloc(sizeof(char *) * (strs_n + 2));
	if (!result)
		return (0);
	i = 0;
	while (strs[i])
	{
		result[i] = ft_strdup(strs[i]);
		i++;
	}
	result[i] = ft_strdup(str);
	i++;
	result[i] = 0;
	return (result);
}

char	**ft_strscopy(char **strs)
{
	int		strs_n;
	int		i;
	char	**result;

	strs_n = 0;
	while (strs[strs_n])
		strs_n++;
	result = malloc(sizeof(char *) * (strs_n + 1));
	if (!result)
		return (0);
	i = 0;
	while (strs[i])
	{
		result[i] = ft_strdup(strs[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}
