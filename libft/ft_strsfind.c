/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsfind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:28 by kricky            #+#    #+#             */
/*   Updated: 2021/11/14 15:22:24 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strsfind(const char **strs, const char *str)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (ft_strcmp(strs[i], str) == 0)
			return (1);
		i++;
	}
	return (0);
}
