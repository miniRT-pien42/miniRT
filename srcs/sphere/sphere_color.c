#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "helpers.h"
#include "ray.h"

static t_vector	get_position_on_sphere(\
	t_scene *scene, t_vector ray, double distance)
{
	return (vec_add(scene->camera->pos, vec_scalar(ray, distance)));
}

static t_vector	get_normal_on_sphere(t_vector position, t_sphere *sphere, bool is_camera_inside)
{
	t_vector	normal;

	if (is_camera_inside)
	{
		normal = vec_normalize(\
			vec_subtract(sphere->center, position));
	}
	else
	{
		normal = vec_normalize(\
			vec_subtract(position, sphere->center));
	}
	return (normal);
}

bool	is_inside_sphere(t_vector pos_target, t_sphere *sphere, t_vector ray)
{
	double	distances[2];
	double	discriminant;

	discriminant = calc_discriminant_for_sphere(\
		ray, sphere, pos_target, distances);
	if (discriminant < 0)
		return (NAN);//todo: ここにはこないはずだけど念の為
	if (distances[0] * distances[1] < 0)
		return (true);
	return (false);
}

static t_intersection	get_intersection_sphere(\
	t_scene *scene, t_sphere *sphere, t_vector ray)
{
	t_intersection	intersection;
	bool			is_camera_inside;

	is_camera_inside = is_inside_sphere(scene->camera->pos, sphere, ray);
	intersection.object = sphere;
	intersection.distance = get_distance_to_sphere(ray, scene, sphere);
	intersection.position = \
		get_position_on_sphere(scene, ray, intersection.distance);
	intersection.normal = \
		get_normal_on_sphere(intersection.position, intersection.object, is_camera_inside);
	intersection.l_dot = get_l_dot(scene, intersection, is_camera_inside);
	return (intersection);
}

t_rgb	ray_tracing_sphere(\
	t_scene *scene, t_sphere *nearest_object, t_vector ray)
{
	t_intersection	intersection;
	t_material		material;

	//交点の情報を取得
	intersection = get_intersection_sphere(scene, nearest_object, ray);
	//lux_totalを環境光で初期化。影にならない場合はlightの明るさもadd
	material.lux_total = get_lux_ambient(scene->light_ambient);
	//影になるか判定。ならない場合のみifに入ってlightの明るさ計算
	if (intersection.l_dot != NO_INCIDENT)
	{
		material.lux_light = \
			get_lux_light(scene->light, nearest_object->color, intersection.l_dot);
		material.lux_total = \
			get_lux_total(material.lux_total, material.lux_light);
	}
	material.color = (t_rgb){material.lux_total.r * 255, \
		material.lux_total.g * 255, material.lux_total.b * 255};
	return (material.color);
}