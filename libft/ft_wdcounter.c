/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wdcounter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:39 by kricky            #+#    #+#             */
/*   Updated: 2021/09/01 10:36:40 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wdcounter(const char *str, char separator)
{
	int	i;
	int	finded;
	int	counter;

	i = 0;
	finded = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && finded == 0 && ++counter)
			finded = 1;
		else if (str[i] == separator)
			finded = 0;
		i++;
	}
	return (counter);
}
