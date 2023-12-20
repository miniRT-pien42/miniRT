#include "ft_deque.h"
#include "libft.h"
#include "scene.h"
#include "parse.h"
#include "ft_deque.h"

t_vector	set_axis_base(void)
{
	return ((t_vector){.x = AXIS_BASE_X, .y = AXIS_BASE_Y, .z = AXIS_BASE_Z});
}

static void	convert_line_with_identifier(t_deque_node *node, t_scene *scene)
{
	char	**line;
	char	*identifier;

	line = (char **)node->content;
	identifier = line[0];
	if (ft_streq(identifier, TYPE_AMBIENT))
		scene->light_ambient = init_light_ambient((const char **)line);
	else if (ft_streq(identifier, TYPE_CAMERA))
		scene->camera = init_camera((const char **)line);
	else if (ft_streq(identifier, TYPE_LIGHT))
		scene->light = init_light((const char **)line);
	else if (ft_streq(identifier, TYPE_PLANE))
		add_to_list_object(scene->list_object, (const char **)line, PLANE);
	else if (ft_streq(identifier, TYPE_SPHERE))
		add_to_list_object(scene->list_object, (const char **)line, SPHERE);
	else if (ft_streq(identifier, TYPE_CYLINDER))
		add_to_list_object(scene->list_object, (const char **)line, CYLINDER);
	// else
	// 	return (FAILURE);
	// return (SUCCESS);
}

void	parse_lines_to_scene(t_deque *lines, t_scene *scene)
{
	t_deque_node	*node;

	node = lines->node;
	while (node)
	{
		convert_line_with_identifier(node, scene);
		// todo: return (FAILURE);
		node = node->next;
	}
	// todo: return (SUCCESS);
}

void	init_scene(t_scene *scene)
{
	scene->list_object = deque_new();
}
