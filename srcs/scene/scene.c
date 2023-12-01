#include "ft_deque.h"
#include "libft.h"
#include "scene.h"
#include "parse.h"

t_vector	set_axis_base(void)
{
	return ((t_vector){AXIS_BASE_X, AXIS_BASE_Y, AXIS_BASE_Z});
}

static void	convert_line_with_identifier(t_deque_node *node, t_scene *scene)
{
	char	**line;
	char	*identifier;

	line = (char **)node->content;
	identifier = line[0];
	if (ft_streq(identifier, "A"))
		scene->light_ambient = init_light_ambient((const char **)line);
	else if (ft_streq(identifier, "C"))
		scene->camera = init_camera((const char **)line);
	else if (ft_streq(identifier, "L"))
		scene->light = init_light((const char **)line);
	// else if (ft_streq(identifier, "pl"))
	// 	scene->list_sphere = init_plane(line);
	// else if (ft_streq(identifier, "sp"))
	// 	add_to_list_object(scene, (const char **)line); // todo
	// else if (ft_streq(identifier, "cy"))
	// 	scene->list_sphere = init_cylinder(line);
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
	scene->camera = NULL;
	scene->light_ambient = NULL;
	scene->light = NULL;
	scene->list_object = init_object();
	// scene->center_screen = get_center_screen(scene->camera);
	scene->center_screen = (t_vector){0, 0, 0};
	// scene->rotation_angle = 
	// 	get_angle(set_axis_base(), scene->camera->dir_n);
	scene->rotation_angle = 0;
}
