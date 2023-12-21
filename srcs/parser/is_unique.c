#include "ft_deque.h"
#include "libft.h"
#include "parse.h"
#include "scene.h"
#include <stdbool.h>

static void	init_exist_of_scene(bool *is_scene_exists, const size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		is_scene_exists[i] = false;
		i++;
	}
}

static t_identifier	set_identifier(const char *head_line)
{
	if (head_line == NULL)
		return (ID_OTHER);
	if (ft_strcmp(head_line, TYPE_AMBIENT) == 0)
		return (ID_AMBIENT);
	if (ft_strcmp(head_line, TYPE_CAMERA) == 0)
		return (ID_CAMERA);
	if (ft_strcmp(head_line, TYPE_LIGHT) == 0)
		return (ID_LIGHT);
	return (ID_OTHER);
}

static bool	is_unique(bool *is_scene_exists)
{
	return (is_scene_exists[ID_AMBIENT] \
			&& is_scene_exists[ID_CAMERA] \
			&& is_scene_exists[ID_LIGHT]);
}

// A,C,L must unique.
bool	is_scene_value_unique(const t_deque *lines)
{
	bool			is_scene_exists[3];
	t_deque_node	*node;
	char			**line;
	t_identifier	id;

	init_exist_of_scene(is_scene_exists, 3);
	node = lines->node;
	while (node)
	{
		line = (char **)node->content;
		id = set_identifier(line[0]);
		if (id == ID_AMBIENT || id == ID_CAMERA || id == ID_LIGHT)
		{
			if (is_scene_exists[id])
				return (false);
			is_scene_exists[id] = true;
		}
		node = node->next;
	}
	return (is_unique(is_scene_exists));
}
