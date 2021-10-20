/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:26 by kricky            #+#    #+#             */
/*   Updated: 2021/10/20 15:57:08 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
