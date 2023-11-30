#include "ft_deque.h"
#include "libft.h"

t_deque	*deque_new(void)
{
	t_deque	*deque;

	deque = (t_deque *)x_malloc(sizeof(t_deque));
	deque->node = NULL;
	deque->size = 0;
	return (deque);
}
