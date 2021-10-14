/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:10 by kricky            #+#    #+#             */
/*   Updated: 2021/09/01 10:36:11 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_ilen(int n)
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

void	ft_putnbr_fd(int n, int fd)
{
	int			i;
	int long	number;
	int			size;
	char		nbr[10000];

	i = 0;
	size = ft_ilen(n);
	number = n;
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
	i = 0;
	while (nbr[i] != '\0')
		write(fd, &nbr[i++], 1);
}
