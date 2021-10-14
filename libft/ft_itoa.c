/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:35:34 by kricky            #+#    #+#             */
/*   Updated: 2021/09/01 10:35:34 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_intlen(int n)
{
	int			i;
	int long	number;

	i = 0;
	number = n;
	if (number < 0)
	{
		number *= -1;
		i++;
	}
	else if (number == 0)
		i++;
	while (number > 0)
	{
		number = number / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int long	number;
	int			size;
	char		*nbr;

	size = ft_intlen(n);
	number = n;
	nbr = malloc(sizeof(char) * (size + 1));
	if (!nbr)
		return (0);
	nbr[size--] = '\0';
	if (number < 0)
	{
		nbr[0] = '-';
		number *= -1;
	}
	else if (number == 0)
		nbr[size] = '0';
	while (number > 0)
	{
		nbr[size--] = '0' + (number % 10);
		number = number / 10;
	}
	return (nbr);
}
