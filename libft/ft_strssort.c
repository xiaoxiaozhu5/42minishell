/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strssort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:28 by kricky            #+#    #+#             */
/*   Updated: 2021/11/06 16:46:47 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strssort(char **strs)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[j])
		{
			if (ft_strncmp(strs[i], strs[j], ft_strlen(strs[i])) < 0)
			{
				temp = strs[i];
				strs[i] = strs[j];
				strs[j] = temp;
			}
			j++;
		}
		i++;
	}
}
