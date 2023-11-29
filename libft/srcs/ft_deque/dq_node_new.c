#include "ft_deque.h"
#include "libft.h"

t_deque_node	*deque_node_new(void *content)
{
	t_deque_node	*node;

	node = (t_deque_node *)x_malloc(sizeof(t_deque_node));
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
