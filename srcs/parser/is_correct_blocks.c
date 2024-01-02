#include "ft_deque.h"
#include "libft.h"
#include "parse.h"

// 3 : A [] []
// 4 : C [] [] []
// 4 : L [] [] []
// 4 : sp [] [] []
// 4 : pl [] [] []
// 6 : cy [] [] [] [] []
static bool	is_correct_each_number_of_blocks(char **line)
{
	size_t			block_size;
	t_identifier	id;

	id = set_identifier(line[0]);
	block_size = ft_len_2d_array((const char **)line);
	if (id == ID_AMBIENT)
		return (block_size == ELEM_COUNT_AMBIENT);
	if (id == ID_CAMERA)
		return (block_size == ELEM_COUNT_CAMERA);
	if (id == ID_LIGHT)
		return (block_size == ELEM_COUNT_LIGHT);
	if (id == ID_PLANE)
		return (block_size == ELEM_COUNT_PLANE);
	if (id == ID_SPHERE)
		return (block_size == ELEM_COUNT_SPHERE);
	if (id == ID_CYLINDER)
		return (block_size == ELEM_COUNT_CYLINDER);
	return (false);
}

bool	is_correct_number_of_blocks(const t_deque *lines)
{
	t_deque_node	*node;
	char			**line;

	node = lines->node;
	while (node)
	{
		line = (char **)node->content;
		if (!is_correct_each_number_of_blocks(line))
			return (false);
		node = node->next;
	}
	return (true);
}
