/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:15 by kricky            #+#    #+#             */
/*   Updated: 2021/11/01 17:12:26 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_striclear(char *str, int f, int s)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (result)
	{
		while (str[i] != '\0')
		{
			if (i != f && i != s)
			{
				result[j] = str[i];
				j++;
			}
			i++;
		}
		result[j] = '\0';
		return (result);
	}
	return (0);
}
