#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "helpers.h"
#include "ray.h"

static t_vector	get_position_on_plane(t_scene *scene, t_vector ray, double distance)
{
	return (vec_add(scene->camera->pos, vec_scalar(ray, distance)));
}

static t_intersection	get_intersection_plane(\
	t_scene *scene, t_plane *plane, t_vector ray)
{
	t_intersection	intersection;

	intersection.object = plane;
	intersection.distance = get_distance_to_plane(ray, scene->camera->pos, plane);
	intersection.position = \
		get_position_on_plane(scene, ray, intersection.distance);
	intersection.normal = plane->normal;
	intersection.incident = \
		vec_normalize(vec_subtract(scene->light->pos, intersection.position));
	intersection.l_dot = get_l_dot(intersection);
	return (intersection);
}

t_rgb	ray_tracing_plane(\
	t_scene *scene, t_plane *nearest_object, t_vector ray)
{
	t_intersection	intersection;
	t_material		material;

	//交点の情報を取得
	intersection = get_intersection_plane(scene, nearest_object, ray);
	//lux_totalを環境光で初期化。影にならない場合はlightの明るさもadd
	material.lux_total = get_lux_ambient(scene->light_ambient);
	//影になるか判定。ならない場合のみifに入ってlightの明るさ計算
	//if (!is_shadow_plane(scene, intersection))
	//{
	material.lux_light = \
		get_lux_light(scene->light, nearest_object->color, intersection.l_dot);
	material.lux_total = \
		get_lux_total(material.lux_total, material.lux_light);
	//}
	material.color = (t_rgb){material.lux_total.r * 255, \
		material.lux_total.g * 255, material.lux_total.b * 255};
	return (material.color);
}