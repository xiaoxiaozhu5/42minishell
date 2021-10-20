#include "ft_minishell.h"

t_node	*ft_node_create()
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->next = NULL;
	new->command = NULL;
	new->flags = NULL;
	new->args = NULL;
	new->c_end = '\0';
	return (new);
}

t_node	*ft_list_create_back(t_node **lst)
{
	t_node	*iter;

	if (*lst != 0)
	{
		iter = *lst;
		while (iter->next != 0)
		{
			iter = iter->next;
		}
		iter->next = ft_node_create();
	}
	else
		*lst = ft_node_create();
	return (*lst);
}
