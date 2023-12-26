#include "ft_deque.h"
#include "libft.h"
#include "parse.h"
#include "scene.h"
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

t_identifier	set_identifier(const char *head_line)
{
	if (head_line == NULL)
		return (ID_OTHER);
	if (ft_strcmp(head_line, TYPE_AMBIENT) == 0)
		return (ID_AMBIENT);
	if (ft_strcmp(head_line, TYPE_CAMERA) == 0)
		return (ID_CAMERA);
	if (ft_strcmp(head_line, TYPE_LIGHT) == 0)
		return (ID_LIGHT);
	if (ft_strcmp(head_line, TYPE_PLANE) == 0)
		return (ID_PLANE);
	if (ft_strcmp(head_line, TYPE_SPHERE) == 0)
		return (ID_SPHERE);
	if (ft_strcmp(head_line, TYPE_CYLINDER) == 0)
		return (ID_CYLINDER);
	return (ID_OTHER);
}

// if is_correct_number_of_blocks() passed, the identifiers are valid.
bool	is_valid_lines(t_deque **lines)
{
	if (*lines == NULL || deque_is_empty(*lines))
		return (false);
	remove_empty_lines(lines);
	if (!is_correct_number_of_blocks(*lines))
		return (false);
	if (!has_at_least_3_lines((const t_deque *)*lines))
		return (false);
	if (!is_scene_value_unique((const t_deque *)*lines))
		return (false);
	if (!is_correct_value_counts((const t_deque *)*lines))
		return (false);
	return (true);
}
