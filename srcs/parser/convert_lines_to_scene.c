#include "ft_deque.h"
#include "scene.h"
#include "object.h"
#include "parse.h"

static void	convert_line_with_identifier(t_deque_node *node, t_scene *scene)
{
	char			**line;
	t_identifier	id;

	line = (char **)node->content;
	id = set_identifier(line[0]);
	if (id == ID_AMBIENT)
		scene->light_ambient = init_light_ambient((const char **)line);
	else if (id == ID_CAMERA)
		scene->camera = init_camera((const char **)line);
	else if (id == ID_LIGHT)
		scene->light = init_light((const char **)line);
	else if (id == ID_PLANE)
		add_to_list_object(scene->list_object, (const char **)line, PLANE);
	else if (id == ID_SPHERE)
		add_to_list_object(scene->list_object, (const char **)line, SPHERE);
	else if (id == ID_CYLINDER)
		add_to_list_object(scene->list_object, (const char **)line, CYLINDER);
	// else
	// 	return (FAILURE);
	// return (SUCCESS);
}

void	parse_lines_to_scene(t_deque *lines, t_scene *scene)
{
	t_deque_node	*node;

	init_scene(scene);
	node = lines->node;
	while (node)
	{
		convert_line_with_identifier(node, scene);
		// todo: return (FAILURE);
		node = node->next;
	}
	// todo: return (SUCCESS);
}
