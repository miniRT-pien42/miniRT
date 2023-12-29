#include "object.h"
#include "ray.h"
#include "scene.h"
#include <math.h>

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
