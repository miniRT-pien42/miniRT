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

static t_vector	get_normal_on_sphere(\
	t_scene *scene, t_vector ray, t_vector position)
{
	t_vector	normal;

	normal = vec_normalize(\
			vec_subtract(intersection.position, sphere->center));//todo: カメラ内側なら反転
	return (normal);
}

static t_vector	get_incident_on_sphere(t_vector right_pos, t_vector is_pos)
{
	return (\
		vec_normalize(vec_subtract(right_pos, is_pos)));
}

static t_intersection	get_intersection_sphere(\
	t_scene *scene, t_sphere *sphere, t_vector ray)
{
	t_intersection	intersection;

	intersection.object = sphere;
	intersection.distance = get_distance_to_sphere(ray, scene, sphere);
	intersection.position = \
		get_position_on_sphere(scene, ray, intersection.distance);
	intersection.normal = \
		get_normal_on_sphere(scene, ray, intersection.position);
	intersection.incident = \
		get_incident_on_sphere(scene->light->pos, intersection.position);
	intersection.l_dot = get_l_dot(intersection);
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