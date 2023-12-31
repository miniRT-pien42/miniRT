#include <stdio.h>
#include "ft_deque.h"

void	deque_print(t_deque *deque, void (*print)(void *))
{
	t_deque_node	*node;

	if (deque_is_empty(deque))
	{
		printf("deque is empty!\n");
		printf("---------------------\n");
		return ;
	}
	printf("content: \n");
	node = deque->node;
	while (node)
	{
		print(node->content);
		node = node->next;
	}
	printf("\nsize  : %zu\n", deque->size);
	printf("---------------------\n");
}

void	debug_deque_print(\
				t_deque *deque, const char *func_name, void (*print)(void *))
{
	printf(">>> %s\n", func_name);
	deque_print(deque, print);
}
