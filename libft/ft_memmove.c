/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:02 by kricky            #+#    #+#             */
/*   Updated: 2021/09/01 10:36:03 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmp_dst;
	char	*tmp_src;

	if (!dst && !src)
		return (0);
	tmp_dst = (char *)dst;
	tmp_src = (char *)src;
	if (src >= dst)
		ft_memcpy(dst, src, len);
	else
	{
		while (len--)
			tmp_dst[len] = tmp_src[len];
	}
	return (dst);
}
