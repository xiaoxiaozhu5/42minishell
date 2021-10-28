/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:05 by kricky            #+#    #+#             */
/*   Updated: 2021/10/28 14:53:17 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrncmp(const int n1, const int n2)
{
	if (n1 > n2)
		return (n1 - n2);
	else if (n1 < n2)
		return (n2 - n1);
	return (0);
}

int	ft_nbrcmp(const int n1, const int n2)
{
	if (n1 > n2)
		return (1);
	else if (n1 < n2)
		return (-1);
	return (0);
}
