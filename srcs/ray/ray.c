#include <stdlib.h>
#include "object.h"
#include "helpers.h"

static void	get_info_intersection(
		const t_scene *scene, t_intersection *ptr_nearest, t_vector ray)
{
	const t_sphere	*sphere = ptr_nearest->object;

	ptr_nearest->position = vec_add(scene->camera->pos, \
		vec_scalar(ray, ptr_nearest->distance));
	ptr_nearest->incident = vec_normalize(\
			vec_subtract(scene->light->pos, ptr_nearest->position));
	if (is_camera_inside(ptr_nearest, scene->camera->pos))
		ptr_nearest->normal = vec_normalize(\
			vec_subtract(sphere->center, ptr_nearest->position));
	else
		ptr_nearest->normal = vec_normalize(\
			vec_subtract(ptr_nearest->position, sphere->center));
}

static t_rgb_f	get_lux_ambient(const t_light_ambient *ambient)
{
	t_rgb_f	lux_ambient;

	lux_ambient.r = ambient->color.r / 255.0 * ambient->bright;
	lux_ambient.g = ambient->color.g / 255.0 * ambient->bright;
	lux_ambient.b = ambient->color.b / 255.0 * ambient->bright;
	return (lux_ambient);
}

static t_rgb_f	get_lux_light(const t_light *light, t_rgb color, double l_dot)
{
	t_rgb_f	lux_light;

	lux_light.r = color.r / 255.0 * light->bright * l_dot;
	lux_light.g = color.g / 255.0 * light->bright * l_dot;
	lux_light.b = color.b / 255.0 * light->bright * l_dot;
	return (lux_light);
}

static t_rgb_f	get_lux_total(t_rgb_f lux_ambient, t_rgb_f lux_light)
{
	t_rgb_f	lux_total;

	lux_total.r = clipping(lux_ambient.r + lux_light.r, 0, 1);
	lux_total.g = clipping(lux_ambient.g + lux_light.g, 0, 1);
	lux_total.b = clipping(lux_ambient.b + lux_light.b, 0, 1);
	return (lux_total);
}

//シーンにおける，単一のレイでの光線追跡を行い，その点での色を返す．
t_rgb	ray_tracing(
		const t_scene *scene, t_intersection nearest, t_vector ray)
{
	t_material		material;
	//t_vector		shadow_ray;
	double			l_dot;
	const t_sphere	*sphere = nearest.object;

	//check_light_inside_sphere(scene, &nearest);
	get_info_intersection(scene, &nearest, ray);
	material.lux_ambient = get_lux_ambient(scene->light_ambient);
	material.lux_total = material.lux_ambient;
//	if (sphere->is_camera_inside == sphere->is_light_inside)
//	{
//		shadow_ray = vec_subtract(nearest.position, scene->light->pos);
//		if (!is_shadow_by_sphere(shadow_ray, scene, sphere))
//		{
//			l_dot = vec_dot(nearest.incident, nearest.normal);
//			l_dot = clipping(l_dot, 0, 1);
//			material.lux_light = \
//				get_lux_light(scene->light, sphere->color, l_dot);
//			material.lux_total = \
//				get_lux_total(material.lux_ambient, material.lux_light);
//		}
//	}
	l_dot = vec_dot(nearest.incident, nearest.normal);
	l_dot = clipping(l_dot, 0, 1);
	material.lux_light = \
		get_lux_light(scene->light, sphere->color, l_dot);
	material.lux_total = \
		get_lux_total(material.lux_ambient, material.lux_light);
	material.color = (t_rgb){material.lux_total.r * 255, \
		material.lux_total.g * 255, material.lux_total.b * 255};
	return (material.color);
}
