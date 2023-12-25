#include "ft_deque.h"
#include "libft.h"
#include "parse.h"
#include <stdbool.h>

// remove empty lines and pack into a new deque.
static void	remove_empty_lines(t_deque **lines)
{
	t_deque_node	*pop_node;
	char			**line;
	t_deque			*new_lines;

	new_lines = deque_new();
	while (!deque_is_empty(*lines))
	{
		pop_node = deque_pop_front(*lines);
		line = (char **)pop_node->content;
		if (line == NULL || ft_streq(line[0], "\n"))
		{
			deque_clear_node(&pop_node, del_lines);
			continue ;
		}
		deque_add_back(new_lines, pop_node);
	}
	deque_clear_all(lines, del_lines);
	*lines = new_lines;
}

// 3 = A, C, L
static bool	has_at_least_3_lines(const t_deque *lines)
{
	return (lines->size >= AT_LEAST_LINES);
}

bool	is_valid_lines(t_deque **lines)
{
	if (*lines == NULL || deque_is_empty(*lines))
		return (false);
	remove_empty_lines(lines);
	if (!is_correct_number_of_blocks(*lines))
		return (false);
	if (!has_at_least_3_lines((const t_deque *)*lines))
		return (false);
	return (true);
}
