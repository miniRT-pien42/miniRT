#include "ft_deque.h"
#include "parse.h"

static size_t	count_value(const char *s)
{
	size_t	value_count;

	value_count = 0;
	while (*s)
	{
		if (*s == ',')
			value_count++;
		s++;
	}
	return (value_count + 1);
}

static bool	is_correct_value_count(\
		const char **line, const size_t *value_counts, const size_t elem_count)
{
	size_t	i;
	size_t	value_count;

	i = 0;
	while (i < elem_count)
	{
		value_count = count_value(line[i]);
		if (value_count != value_counts[i])
			return (false);
		i++;
	}
	return (true);
}

// A    [1]   [1,2,3]
// C  [1,2,3] [1,2,3]   [1]
// L  [1,2,3]   [1]   [1,2,3]
// pl [1,2,3] [1,2,3] [1,2,3]
// sp [1,2,3]   [1]   [1,2,3]
// cy [1,2,3] [1,2,3]   [1]   [1] [1,2,3]
static bool	is_correct_value_counts_in_each_info(\
									const char **line, const t_identifier id)
{
	if (id == ID_AMBIENT)
		return (is_correct_value_count(\
					line, (size_t []){1, 3}, ELEM_COUNT_AMBIENT - 1));
	if (id == ID_CAMERA)
		return (is_correct_value_count(\
					line, (size_t []){3, 3, 1}, ELEM_COUNT_CAMERA - 1));
	if (id == ID_LIGHT)
		return (is_correct_value_count(\
					line, (size_t []){3, 1, 3}, ELEM_COUNT_LIGHT - 1));
	if (id == ID_PLANE)
		return (is_correct_value_count(\
					line, (size_t []){3, 3, 3}, ELEM_COUNT_PLANE - 1));
	if (id == ID_SPHERE)
		return (is_correct_value_count(\
					line, (size_t []){3, 1, 3}, ELEM_COUNT_SPHERE - 1));
	if (id == ID_CYLINDER)
		return (is_correct_value_count(\
					line, (size_t []){3, 3, 1, 1, 3}, ELEM_COUNT_CYLINDER - 1));
	return (false);
}

bool	is_correct_value_counts(const t_deque *lines)
{
	t_deque_node	*node;
	char			**line;
	t_identifier	id;

	node = lines->node;
	while (node)
	{
		line = (char **)node->content;
		id = set_identifier(line[0]);
		if (!is_correct_value_counts_in_each_info((const char **)&line[1], id))
			return (false);
		node = node->next;
	}
	return (true);
}
