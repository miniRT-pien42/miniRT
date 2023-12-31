#include "ft_deque.h"
#include <stdlib.h>

t_deque	*deque_new(void)
{
	t_deque	*deque;

	deque = (t_deque *)malloc(sizeof(t_deque));
	if (deque == NULL)
		return (NULL);
	deque->node = NULL;
	deque->size = 0;
	return (deque);
}
