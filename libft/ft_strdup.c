/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:19 by kricky            #+#    #+#             */
/*   Updated: 2021/10/21 16:20:30 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*wer;

	i = 0;
	while (s1[i])
		i++;
	wer = (char *)malloc((i + 1) * sizeof(char));
	if (!(wer))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		wer[i] = s1[i];
		i++;
	}
	wer[i] = '\0';
	return (wer);
}

