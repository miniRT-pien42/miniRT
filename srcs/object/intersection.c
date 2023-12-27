#include "object.h"
#include "ray.h"
#include "scene.h"
#include <math.h>

bool	is_shadow_intersection(\
	t_scene *scene, t_intersection intersection, t_vector ray_shadow)
{
	t_deque_node	*current_node;
	double			new_distance;
	double			light_distance;

	current_node = scene->list_object->node;
	light_distance = \
		get_distance(ray_shadow, scene->light->pos, intersection.object);
	while (current_node)
	{
		if (current_node->content != intersection.object)
		{
			new_distance = get_distance(\
				ray_shadow, scene->light->pos, current_node->content);
			if (!isnan(new_distance) && new_distance < light_distance)
				return (true);
		}
		current_node = current_node->next;
	}
	return (false);
}

static t_vector	get_position_on_object(\
	t_scene *scene, t_vector ray, double distance)
{
	return (vec_add(scene->camera->pos, vec_scalar(ray, distance)));
}

static t_vector	get_normal(\
	t_scene *scene, t_intersection intersection, t_vector ray, t_shape type)
{
	t_vector	normal;

	if (type == SPHERE)
		normal = get_normal_on_sphere(scene, intersection, ray);
	else if (type == PLANE)
		normal = ((t_plane *)intersection.object)->normal;
	else if (type == CYLINDER)
		normal = get_normal_on_cylinder(scene, intersection, ray);
	else
		normal = (t_vector){.x = 0, .y = 0, .z = 0};
	return (normal);
}

t_intersection	get_intersection(\
	t_scene *scene, void *nearest_object, t_vector ray)
{
	t_intersection	intersection;
	const t_shape	type = get_object_type(nearest_object);

	intersection.object = nearest_object;
	intersection.distance = \
		get_distance(ray, scene->camera->pos, intersection.object);
	intersection.position = \
		get_position_on_object(scene, ray, intersection.distance);
	intersection.normal = get_normal(scene, intersection, ray, type);
	//PLANE法線をcamera側に
	if (type == PLANE && \
		vec_dot(intersection.normal, vec_normalize(\
		vec_subtract(intersection.position, scene->camera->pos))) > 0)
	{
		intersection.normal = vec_scalar(intersection.normal, -1);
	}
	intersection.l_dot = get_l_dot(scene, intersection);
	return (intersection);
}
