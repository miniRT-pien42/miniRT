#include "ft_deque.h"
#include "libft.h"
#include "parse.h"
#include "scene.h"
#include <stdbool.h>

static bool	has_type_3_blocks(const char *type)
{
	return (ft_streq(type, TYPE_AMBIENT));
}

static bool	has_type_4_blocks(const char *type)
{
	return (ft_streq(type, TYPE_CAMERA) \
			|| ft_streq(type, TYPE_LIGHT) \
			|| ft_streq(type, TYPE_PLANE) \
			|| ft_streq(type, TYPE_SPHERE));
}

static bool	has_type_6_blocks(const char *type)
{
	return (ft_streq(type, TYPE_CYLINDER));
}

// A: 3 blocks, C/L/sp/pl: 4 blocks, cy: 6 blocks
static bool	is_correct_each_number_of_blocks(char **line)
{
	size_t	block_size;
	char	*type;

	type = line[0];
	block_size = ft_len_2d_array((const char **)line);
	if (has_type_3_blocks(type))
		return (block_size == 3);
	else if (has_type_4_blocks(type))
		return (block_size == 4);
	else if (has_type_6_blocks(type))
		return (block_size == 6);
	else
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
