/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:35:41 by kricky            #+#    #+#             */
/*   Updated: 2021/09/01 10:35:41 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*iter;
	t_list	*temp;

	temp = *lst;
	while (temp)
	{
		iter = temp->next;
		if (del)
			del(temp->content);
		free(temp);
		temp = iter;
	}
	*lst = 0;
}
