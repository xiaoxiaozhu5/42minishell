/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:28 by kricky            #+#    #+#             */
/*   Updated: 2021/11/14 14:26:50 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strs_push_front(char **strs, const char *str)
{
	int		i;
	int		j;
	char	**result;

	result = malloc(sizeof(char *) * (ft_strslen(strs) + 2));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	result[j++] = ft_strdup(str);
	while (strs[i])
	{
		result[j++] = ft_strdup(strs[i]);
		i++;
	}
	result[j] = 0;
	return (result);
}
