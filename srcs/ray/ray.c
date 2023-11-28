#include <stdlib.h>
#include "object.h"
#include "utils.h"

static void	get_info_intersection(
		const t_scene *scene, t_intersection *ptr_nearest, t_vector ray)
{
	ptr_nearest->position = vec_add(scene->camera->pos, \
		vec_scalar(ray, ptr_nearest->distance));
	ptr_nearest->incident = vec_normalize(\
			vec_subtract(scene->light->pos, ptr_nearest->position));
	if (ptr_nearest->sphere->is_camera_inside)
		ptr_nearest->normal = vec_normalize(\
			vec_subtract(ptr_nearest->sphere->center, ptr_nearest->position));
	else
		ptr_nearest->normal = vec_normalize(\
			vec_subtract(ptr_nearest->position, ptr_nearest->sphere->center));
}

static t_rgb_f	get_l_a(const t_light_ambient *ambient)
{
	t_rgb_f	l_a;

	l_a.r = ambient->color.r / 255.0 * ambient->bright;
	l_a.g = ambient->color.g / 255.0 * ambient->bright;
	l_a.b = ambient->color.b / 255.0 * ambient->bright;
	return (l_a);
}

static t_rgb_f	get_l_d(const t_light *light, t_rgb color, double l_dot)
{
	t_rgb_f	l_d;

	l_d.r = color.r / 255.0 * light->bright * l_dot;
	l_d.g = color.g / 255.0 * light->bright * l_dot;
	l_d.b = color.b / 255.0 * light->bright * l_dot;
	return (l_d);
}

static t_rgb_f	get_l_r(t_rgb_f l_a, t_rgb_f l_d)
{
	t_rgb_f	l_r;

	l_r.r = clipping(l_a.r + l_d.r, 0, 1);
	l_r.g = clipping(l_a.g + l_d.g, 0, 1);
	l_r.b = clipping(l_a.b + l_d.b, 0, 1);
	return (l_r);
}

//シーンにおける，単一のレイでの光線追跡を行い，その点での色を返す．
t_rgb	ray_tracing(
		const t_scene *scene, t_intersection nearest, t_vector ray)
{
	t_material	material;
	t_vector	shadow_ray;
	double		l_dot;

	check_light_inside_sphere(scene, &nearest);
	get_info_intersection(scene, &nearest, ray);
	material.l_a = get_l_a(scene->light_ambient);
	material.l_r = material.l_a;
	if (nearest.sphere->is_camera_inside == nearest.sphere->is_light_inside)
	{
		shadow_ray = vec_subtract(nearest.position, scene->light->pos);
		if (!is_shadow_by_sphere(shadow_ray, scene, nearest.sphere))
		{
			//todo: (bug)球の内側にlightがある場合、球上部は内、下部は外が照らされる
			l_dot = vec_dot(nearest.incident, nearest.normal);
			l_dot = clipping(l_dot, 0, 1);
			material.l_d = get_l_d(scene->light, nearest.sphere->color, l_dot);
			material.l_r = get_l_r(material.l_a, material.l_d);
		}
	}
	material.color = (t_rgb){\
		material.l_r.r * 255, material.l_r.g * 255, material.l_r.b * 255};
	return (material.color);
}
