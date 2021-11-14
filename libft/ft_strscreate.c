/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscreate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:28 by kricky            #+#    #+#             */
/*   Updated: 2021/11/14 13:17:52 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strscreate(char *str)
{
	char	**strs;

	strs = malloc(sizeof(char *) * 2);
	strs[0] = ft_strdup(str);
	strs[1] = 0;
	return (strs);
}
