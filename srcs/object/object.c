#include <math.h>
#include "scene.h"
#include "ray.h"

t_shape	get_object_type(void *object)
{
	return (*(t_shape *)object);
}

static void	update_nearest_object(t_vector ray, \
	t_scene *scene, t_deque_node *object_current, t_intersection *nearest)
{
	t_shape	type;

	type = get_object_type(object_current->content);
	if (type == SPHERE)
	{
		update_nearest_sphere(\
			ray, scene, (t_sphere *)object_current->content, nearest);
	}
	else if (type == PLANE)
	{
		update_nearest_plane(\
			ray, scene, (t_plane *)object_current->content, nearest);
	}
	else if (type == CYLINDER)
	{
		update_nearest_cylinder(\
			ray, scene, (t_cylinder *)object_current->content, nearest);
	}
}

t_intersection	get_nearest_object(t_vector ray, t_scene *scene)
{
	t_intersection	nearest;
	t_deque_node	*object_current;

	nearest.distance = INFINITY;
	object_current = scene->list_object->node;
	while (object_current)
	{
		update_nearest_object(ray, scene, object_current, &nearest);
		object_current = object_current->next;
	}
	return (nearest);
}

static t_deque_node	*get_new_object_node(const char **line, const t_shape type)
{
	t_deque_node	*node;

	if (type == SPHERE)
		node = deque_node_new(init_sphere(line));
	else if (type == PLANE)
		node = deque_node_new(init_plane(line));
	else if (type == CYLINDER)
		node = deque_node_new(init_cylinder(line));
	else
		node = NULL;
	return (node);
}

void	add_to_list_object(\
					t_deque *list_object, const char **line, const t_shape type)
{
	t_deque_node	*node;

	node = get_new_object_node(line, type);
	deque_add_back(list_object, node);
}
