/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:28 by kricky            #+#    #+#             */
/*   Updated: 2021/11/07 16:32:29 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	s1_length;
	unsigned int	s2_length;

	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	if (s1_length > s2_length)
		return (ft_strncmp(s1, s2, s1_length));
	return (ft_strncmp(s1, s2, s2_length));
}
