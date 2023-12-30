#include "object.h"
#include "parse.h"
#include "result.h"
#include "scene.h"
#include <math.h>
#include <stdlib.h> // free

t_shape	get_object_type(void *object)
{
	if (object == NULL)
		return (SHAPE_NONE);
	return (*(t_shape *)object);
}

// If there are two intersection points, return the distance to the closer one.
static double	get_distance(t_vector ray, t_scene *scene, void *object)
{
	t_shape	type;
	double	distance;

	type = get_object_type(object);
	if (type == SPHERE)
		distance = get_distance_to_sphere(ray, scene, (t_sphere *)object);
	else if (type == PLANE)
		distance = get_distance_to_plane(ray, scene, (t_plane *)object);
	else if (type == CYLINDER)
		distance = get_distance_to_cylinder(ray, scene, (t_cylinder *)object);
	else
		distance = NAN;
	return (distance);
}

void	*get_nearest_object(t_vector ray, t_scene *scene)
{
	t_deque_node	*current_node;
	void			*nearest_object;
	double			nearest_distance;
	double			new_distance;

	current_node = scene->list_object->node;
	nearest_object = NULL;
	nearest_distance = INFINITY;
	while (current_node)
	{
		new_distance = get_distance(ray, scene, current_node->content);
		if (!isnan(new_distance) && new_distance < nearest_distance)
		{
			nearest_distance = new_distance;
			nearest_object = current_node->content;
		}
		current_node = current_node->next;
	}
	return (nearest_object);
}

// only PLANE or SPHERE or CYLINDER
static t_deque_node	*get_new_object_node(\
						const char **line, const t_shape type, t_result *result)
{
	t_deque_node	*node;
	void			*object;

	object = NULL;
	if (type == SPHERE)
		object = (void *)init_sphere(line, result);
	else if (type == PLANE)
		object = (void *)init_plane(line, result);
	else if (type == CYLINDER)
		object = (void *)init_cylinder(line, result);
	node = deque_node_new(object);
	return (node);
}

t_result	add_to_list_object(\
					t_deque *list_object, const char **line, const t_shape type)
{
	t_deque_node	*node;
	t_result		result;

	result = SUCCESS;
	node = get_new_object_node(line, type, &result);
	if (result == FAILURE)
	{
		deque_clear_node(&node, free);
		return (FAILURE);
	}
	deque_add_back(list_object, node);
	return (SUCCESS);
}
