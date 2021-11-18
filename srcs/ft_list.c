#include "ft_minishell.h"

t_node	*ft_node_create(void)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->next = 0;
	new->redirs = 0;
	new->command = 0;
	new->flags = 0;
	new->args = 0;
	new->exec_args = 0;
	new->c_end = '\0';
	new->redir_0 = 0;
	new->redir_1 = 1;
	// new->fds[0] = 0;
	// new->fds[1] = 1;
	return (new);
}

t_redir	*ft_node_redir_create(void)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->next = 0;
	new->type = 0;
	new->value = 0;
	return (new);
}

void	*ft_list_create_back(void **lst, void *new)
{
	t_node	*iter;

	if (*lst != 0)
	{
		iter = *lst;
		while (iter->next != 0)
		{
			iter = iter->next;
		}
		iter->next = new;
		return (iter->next);
	}
	else
		*lst = new;
	return (*lst);
}
