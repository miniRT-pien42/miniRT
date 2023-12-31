#include "object.h"
#include "ray.h"
#include "scene.h"

t_rgb	ray_tracing(t_scene *scene, void *nearest_object, const t_ray *ray)
{
	t_intersection	intersection;
	t_rgb_f			lux_light;
	t_rgb_f			lux_total;
	t_rgb			color;

	intersection = get_intersection(scene, nearest_object, ray);
	lux_total = get_lux_ambient(scene->light_ambient);
	if (intersection.l_dot != NOT_ILLUMINATED)
	{
		lux_light = \
			get_lux_light(scene->light, nearest_object, intersection.l_dot);
		lux_total = add_up_lux_total(lux_total, lux_light);
	}
	color = (t_rgb){.r = lux_total.r * 255, \
		.g = lux_total.g * 255, .b = lux_total.b * 255};
	return (color);
}
