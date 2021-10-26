/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:26 by kricky            #+#    #+#             */
/*   Updated: 2021/10/22 22:18:39 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_find_alnum(char *str, int index_start)
{
	int	i;

	if (!str)
		return (0);
	i = index_start;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (i);
		i++;
	}
	return (0);
}

int	ft_str_find_next(char *str, char c, int index_start)
{
	int	i;

	if (!str)
		return (0);
	i = index_start;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_str_find(char *str, char c, int index_start, int index_end)
{
	int	i;

	if (!str)
		return (0);
	i = index_start;
	while (str[i] != '\0' && i <= index_end)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}
