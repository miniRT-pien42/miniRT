#include "error.h"
#include "ft_deque.h"
#include "object.h"
#include "ray.h"
#include "scene.h"
#include <math.h>

bool	is_shadow_intersection(\
	t_scene *scene, void *object, const t_ray *ray_shadow)
{
	t_deque_node	*current_node;
	double			new_distance;
	double			light_distance;

	current_node = scene->list_object->node;
	light_distance = get_distance(ray_shadow, object);
	while (current_node)
	{
		if (current_node->content != object)
		{
			new_distance = get_distance(ray_shadow, current_node->content);
			if (!isnan(new_distance) && new_distance < light_distance)
				return (true);
		}
		current_node = current_node->next;
	}
	return (false);
}

static t_vector	get_position_on_object(\
	t_scene *scene, const t_ray *ray, double distance)
{
	return (vec_add(scene->camera->pos, vec_scalar(ray->direction, distance)));
}

static t_vector	get_normal(\
	t_intersection intersection, const t_ray *ray, t_shape type)
{
	t_vector	normal;

	normal = (t_vector){.x = 0, .y = 0, .z = 0};
	if (type == SPHERE)
		normal = get_normal_on_sphere(intersection, ray);
	else if (type == PLANE)
		normal = get_normal_on_plane((t_plane *)intersection.object, ray);
	else if (type == CYLINDER)
		normal = get_normal_on_cylinder(intersection, ray);
	return (normal);
}

t_intersection	get_intersection(\
	t_scene *scene, void *nearest_object, const t_ray *ray)
{
	t_intersection	intersection;
	const t_shape	type = get_object_type(nearest_object);

	intersection.object = nearest_object;
	intersection.distance = get_distance(ray, intersection.object);
	intersection.position = \
		get_position_on_object(scene, ray, intersection.distance);
	intersection.normal = get_normal(intersection, ray, type);
	intersection.l_dot = get_l_dot(scene, intersection);
	return (intersection);
}
