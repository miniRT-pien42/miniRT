#include "ft_deque.h"
#include "libft.h"
#include "scene.h"
#include "parse.h"

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
	else if (ft_streq(identifier, "sp"))
		add_to_list_sphere(scene, (const char **)line);
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
	scene->list_sphere = NULL;
}
