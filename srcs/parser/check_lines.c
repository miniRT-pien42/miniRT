#include "ft_deque.h"
#include "libft.h"
#include <stdbool.h>

// todo: to libft?
static size_t	calc_length_of_2d_array(const char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

static bool	has_type_3_blocks(const char *type)
{
	return (ft_streq(type, "A"));
}

static bool	has_type_4_blocks(const char *type)
{
	return (ft_streq(type, "C") \
			|| ft_streq(type, "L") \
			|| ft_streq(type, "sp") \
			|| ft_streq(type, "pl"));
}

static bool	has_type_6_blocks(const char *type)
{
	return (ft_streq(type, "cy"));
}

// A: 3 blocks, C/L/sp/pl: 4 blocks, cy: 6 blocks
static bool	is_correct_each_number_of_blocks(char **line)
{
	size_t	block_size;
	char	*type;

	if (line == NULL)
		return (true);
	type = line[0];
	block_size = calc_length_of_2d_array((const char **)line);
	if (has_type_3_blocks(type))
		return (block_size == 3);
	else if (has_type_4_blocks(type))
		return (block_size == 4);
	else if (has_type_6_blocks(type))
		return (block_size == 6);
	else
		return (false);
}

static bool	is_correct_number_of_blocks(const t_deque *lines)
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

bool	is_valid_lines(const t_deque *lines)
{
	if (lines == NULL || deque_is_empty(lines))
		return (false);
	if (!is_correct_number_of_blocks(lines))
		return (false);
	// todo: add validation
	return (true);
}
