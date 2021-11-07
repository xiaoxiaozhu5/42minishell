/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:26 by kricky            #+#    #+#             */
/*   Updated: 2021/11/02 17:21:23 by                  ###   ########.fr       */
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

int	ft_str_find_in_word(char *str, char c, int start)
{
	int	i;

	if (!str)
		return (0);
	i = start;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		if (str[i] == ' ' || str[i] == '\t')
			return (0);
		i++;
	}
	return (0);
}
