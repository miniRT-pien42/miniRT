#include "ft_deque.h"
#include "scene.h"
#include "object.h"
#include "parse.h"
#include "result.h"

static t_result	convert_line_with_identifier(t_deque_node *node, t_scene *scene)
{
	const char			**line = (const char **)node->content;
	const t_identifier	id = set_identifier(line[0]);
	t_result			result;
	t_deque				*list_object;

	result = SUCCESS;
	list_object = scene->list_object;
	if (id == ID_AMBIENT)
		scene->light_ambient = init_light_ambient((const char **)line, &result);
	else if (id == ID_CAMERA)
		scene->camera = init_camera((const char **)line, &result);
	else if (id == ID_LIGHT)
		scene->light = init_light((const char **)line, &result);
	else if (id == ID_PLANE)
		result = add_to_list_object(list_object, (const char **)line, PLANE);
	else if (id == ID_SPHERE)
		result = add_to_list_object(list_object, (const char **)line, SPHERE);
	else if (id == ID_CYLINDER)
		result = add_to_list_object(list_object, (const char **)line, CYLINDER);
	return (result);
}

t_result	parse_lines_to_scene(t_deque *lines, t_scene *scene)
{
	t_deque_node	*node;
	t_result		result;

	node = lines->node;
	while (node)
	{
		result = convert_line_with_identifier(node, scene);
		if (result == FAILURE)
		{
			deque_clear_all(&lines, del_lines);
			return (FAILURE);
		}
		node = node->next;
	}
	deque_clear_all(&lines, del_lines);
	return (SUCCESS);
}
