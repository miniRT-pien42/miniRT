#include <stdlib.h>
#include <math.h>
#include "scene.h"
#include "object.h"
#include "helpers.h"
#include "ray.h"

bool	is_shadow_plane(\
	t_scene *scene, t_intersection intersection)
{
	const t_vector	ray_shadow = \
		vec_subtract(intersection.position, scene->light->pos);
	t_deque_node	*current_node;
	double			nearest_distance;
	double			new_distance;

	current_node = scene->list_object->node;
	nearest_distance = INFINITY;
	while (current_node)
	{
		new_distance = get_distance(ray_shadow, scene, current_node->content);
		if (!isnan(new_distance) && new_distance < nearest_distance)
			nearest_distance = new_distance;
		current_node = current_node->next;
	}
	if (nearest_distance == INFINITY || \
		nearest_distance != intersection.distance)
		return (false);
	return (true);
}

double	get_l_dot(t_intersection intersection)
{
	double	l_dot;

	l_dot = vec_dot(intersection.incident, intersection.normal);
	l_dot = clipping(l_dot, 0, 1);
	return (l_dot);
}

t_rgb_f	get_lux_ambient(const t_light_ambient *ambient)
{
	t_rgb_f	lux_ambient;

	lux_ambient.r = ambient->color.r / 255.0 * ambient->bright;
	lux_ambient.g = ambient->color.g / 255.0 * ambient->bright;
	lux_ambient.b = ambient->color.b / 255.0 * ambient->bright;
	return (lux_ambient);
}

t_rgb_f	get_lux_light(const t_light *light, t_rgb color, double l_dot)
{
	t_rgb_f	lux_light;

	lux_light.r = color.r / 255.0 * light->bright * l_dot;
	lux_light.g = color.g / 255.0 * light->bright * l_dot;
	lux_light.b = color.b / 255.0 * light->bright * l_dot;
	return (lux_light);
}

t_rgb_f	get_lux_total(t_rgb_f lux_ambient, t_rgb_f lux_light)
{
	t_rgb_f	lux_total;

	lux_total.r = clipping(lux_ambient.r + lux_light.r, 0, 1);
	lux_total.g = clipping(lux_ambient.g + lux_light.g, 0, 1);
	lux_total.b = clipping(lux_ambient.b + lux_light.b, 0, 1);
	return (lux_total);
}
