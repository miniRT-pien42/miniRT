#include "object.h"
#include "ray.h"
#include "scene.h"

t_rgb	ray_tracing(\
	t_scene *scene, void *nearest_object, const t_ray *ray)
{
	t_intersection	intersection;
	t_material		material;

	//交点の情報を取得
	intersection = get_intersection(scene, nearest_object, ray);
	//lux_totalを環境光で初期化。影にならない場合はlightの明るさもadd
	material.lux_total = get_lux_ambient(scene->light_ambient);
	//影になるか判定。ならない場合のみifに入ってlightの明るさ計算
	if (intersection.l_dot != NOT_ILLUMINATED)
	{
		material.lux_light = \
			get_lux_light(scene->light, nearest_object, intersection.l_dot);
		material.lux_total = \
			get_lux_total(material.lux_total, material.lux_light);
	}
	material.color = (t_rgb){.r = material.lux_total.r * 255, \
		.g = material.lux_total.g * 255, .b = material.lux_total.b * 255};
	return (material.color);
}
