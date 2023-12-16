#include <stdlib.h>
#include <math.h>
#include "scene.h"
#include "object.h"
#include "helpers.h"
#include "ray.h"

#include <stdio.h>
bool	is_shadow_intersection(\
	t_scene *scene, t_intersection intersection, bool is_camera_inside)
{
	const t_vector	ray_shadow = \
		vec_subtract(intersection.position, scene->light->pos);
	t_deque_node	*current_node;
	double			new_distance;
	double			light_distance;

	//lightとカメラが球内外に別れている => 影 true
	if (is_camera_inside != is_inside_sphere(scene->light->pos, intersection.object, ray_shadow))
		return (true);
	current_node = scene->list_object->node;
	light_distance = vec_norm(vec_subtract(scene->light->pos, intersection.position));
	while (current_node)
	{
		if (current_node->content == intersection.object)
		{
			current_node = current_node->next;
			continue ;
		}
		//ray_shadowとcurrent_node->contentの交点までの距離取得
		new_distance = get_distance_to_sphere2(ray_shadow, scene->light->pos, current_node->content);
		if (!isnan(new_distance) && new_distance < light_distance)
			return (true);
		current_node = current_node->next;
		printf(": %f %f\n", new_distance, light_distance);
	}
	return (false);
}

double	get_l_dot(t_scene *scene, t_intersection intersection, bool is_camera_inside)
{
	double		l_dot;
	t_vector	incident;

	if (is_shadow_intersection(scene, intersection, is_camera_inside))
		return (NO_INCIDENT);
	incident = vec_normalize(vec_subtract(scene->light->pos, intersection.position));
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
