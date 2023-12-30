#include "ft_deque.h"
#include "object.h"
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
double	get_distance(const t_ray *ray, void *object)
{
	const t_shape	type = get_object_type(object);
	double			distance;

	distance = NAN;
	if (type == SPHERE)
		distance = get_distance_to_sphere(ray, (t_sphere *)object);
	else if (type == PLANE)
		distance = get_distance_to_plane(ray, (t_plane *)object);
	else if (type == CYLINDER)
		distance = get_distance_to_cylinder(ray, (t_cylinder *)object);
	return (distance);
}

void	*get_nearest_object(const t_ray	*ray, t_deque *list_object)
{
	t_deque_node	*current_node;
	void			*nearest_object;
	double			nearest_distance;
	double			new_distance;

	current_node = list_object->node;
	nearest_object = NULL;
	nearest_distance = INFINITY;
	while (current_node)
	{
		new_distance = get_distance(ray, current_node->content);
		if (!isnan(new_distance) && fabs(new_distance) > EPSILON \
			&& new_distance < nearest_distance)
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
