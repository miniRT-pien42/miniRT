#include "scene.h"
#include "object.h"
#include "ray.h"
#include <stdlib.h>
#include <math.h>

static t_ray	get_ray_shadow(t_vector pos_intersection, t_vector pos_light)
{
	t_ray	ray;

	ray.position = pos_light;
	ray.direction = vec_subtract(pos_intersection, pos_light);
	return (ray);
}

double	get_l_dot(\
	t_scene *scene, t_intersection intersection)
{
	double			l_dot;
	t_vector		incident;
	const t_shape	type = get_object_type(intersection.object);
	const t_ray	ray_shadow = get_ray_shadow(intersection.position, scene->light->pos);

	if (type == CYLINDER && \
		is_cylinder_self_shadow(intersection, &ray_shadow))
		return (NOT_ILLUMINATED);
	if (is_shadow_intersection(scene, intersection, &ray_shadow))
		return (NOT_ILLUMINATED);
	incident = vec_normalize(\
		vec_subtract(scene->light->pos, intersection.position));
	l_dot = vec_dot(incident, intersection.normal);
	if (l_dot < 0)
		return (NOT_ILLUMINATED);
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
	t_rgb_f			lux_light;
	const t_shape	type = get_object_type(nearest_object);
	t_rgb			color;

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
