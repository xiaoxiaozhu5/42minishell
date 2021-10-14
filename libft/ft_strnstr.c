/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:30 by kricky            #+#    #+#             */
/*   Updated: 2021/09/01 10:36:30 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	size;
	size_t	i;

	if (*needle == '\0')
		return ((char *)haystack);
	size = ft_strlen(needle);
	i = 0;
	while (haystack[i] != '\0' && len >= size)
	{
		if (*(haystack + i) == *needle)
			if (ft_memcmp(haystack + i, needle, size) == 0)
				return ((char *)haystack + i);
		i++;
		len--;
	}
	return (0);
}
