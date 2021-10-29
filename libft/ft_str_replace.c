/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:36:15 by kricky            #+#    #+#             */
/*   Updated: 2021/10/28 18:36:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_replace(char **str, const char *replace, const char *insert, int start)
{
	int		i;
	char	*temp1;
	char	*temp2;
	char	*e_ptr;
	char	*input;

	input = *str;
	i = 0;
	e_ptr = ft_strnstr(input + start, replace, ft_strlen(input));
	while (e_ptr && &input[i] != e_ptr)
		i++;
	temp2 = ft_substr(input, 0, i);
	temp1 = ft_strjoin(temp2, insert);
	free(temp2);
	temp2 = ft_strjoin(temp1, input + i + ft_strlen(replace));
	free(temp1);
	free(input);
	*str = temp2;
}
