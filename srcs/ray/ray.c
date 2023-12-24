#include "scene.h"
#include "object.h"
#include "ray.h"
#include <stdlib.h>
#include <math.h>

#include <stdio.h>

//todo: lightがinsideならfalse
static bool	is_cylinder_self_shadow(t_intersection intersection, t_vector ray_shadow)
{
	double	distances[2];
	double	discriminant;
	t_ray	ray = (t_ray){.position = intersection.position, .direction = ray_shadow};

	discriminant = calc_discriminant_for_cylinder(&ray, intersection.object, distances);
	if (discriminant < 0)
		return (false);
	if ((distances[0] != distances[1]) && (fabs(fmax(distances[0], distances[1])) < EPSILON))
		return (true);
	return (false);


	return (false);
}

bool	is_shadow_intersection(\
	t_scene *scene, t_intersection intersection, t_vector ray_shadow)
{
	t_deque_node	*current_node;
	double			new_distance;
	double			light_distance;

	current_node = scene->list_object->node;
	light_distance = get_distance(ray_shadow, scene->light->pos, intersection.object);
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

//陰になる要因として
//1: 他の物体の影になる
//2: 自分の影になる
//3: 入射光がない
double	get_l_dot(\
	t_scene *scene, t_intersection intersection)
{
	double		l_dot;
	t_vector	incident;
	const t_shape	type = get_object_type(intersection.object);
	const t_vector	ray_shadow = \
		vec_subtract(intersection.position, scene->light->pos);

	if (type == CYLINDER && is_cylinder_self_shadow(intersection, ray_shadow))
		return (NO_INCIDENT);
	if (is_shadow_intersection(scene, intersection, ray_shadow))
		return (NO_INCIDENT);
	//この画素が影にならないならincident（光の入射をとってきてl_dot計算）
	incident = vec_normalize(\
		vec_subtract(scene->light->pos, intersection.position));
	l_dot = vec_dot(incident, intersection.normal);
	if (l_dot < 0)
		return (NO_INCIDENT);
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

t_rgb_f	get_lux_light(const t_light *light, void *nearest_object, double l_dot)
{
	t_rgb_f	lux_light;
	const t_shape	type = get_object_type(nearest_object);
	t_rgb	color;

	if (type == SPHERE)
		color = ((t_sphere *)nearest_object)->color;
	else if (type == PLANE)
		color = ((t_plane *)nearest_object)->color;
	else if (type == CYLINDER)
		color = ((t_cylinder *)nearest_object)->color;
	else
		exit(EXIT_FAILURE);
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
