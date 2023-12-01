#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "utils.h"
#include "ray.h"

// 解の方程式
static t_discriminant	calc_discriminant(\
		const t_vector ray, const t_vector camera_pos, const t_sphere *sphere)
{
	t_discriminant	discriminant;
	const t_vector	v = vec_subtract(camera_pos, sphere->center);

	discriminant.a = pow(get_scalar(ray), 2);
	discriminant.b = 2.0 * vec_dot(ray, v);
	discriminant.c = pow(get_scalar(v), 2) - pow(sphere->diameter / 2, 2);
	discriminant.d = pow(discriminant.b, 2) - \
		4 * discriminant.a * discriminant.c;
	return (discriminant);
}

// rayとsphereとの距離
static double	calc_distance_to_object(t_discriminant discriminant)
{
	const double	num_bottom = 2.0 * discriminant.a;
	const double	num_top1 = -1 * discriminant.b;
	const double	num_top2 = sqrt(discriminant.d);

	if (discriminant.d == 0)
		return (num_top1 / num_bottom);
	return (positive_and_min(\
				(num_top1 + num_top2) / num_bottom, \
				(num_top1 - num_top2) / num_bottom \
			));
}

// cameraからのrayとsphereとの衝突判定。衝突していればtrueを返す。
static bool	is_intersect_to_sphere(const double d)
{
	return (d >= 0);
}

void	update_nearest_sphere(\
	t_vector ray, t_scene *scene, t_sphere *sphere, t_intersection *ptr_nearest)
{
	t_discriminant	discriminant;
	double			tmp_distance;

	discriminant = calc_discriminant(\
							ray, scene->camera->pos, sphere);
	if (is_intersect_to_sphere(discriminant.d))
	{
		tmp_distance = calc_distance_to_object(discriminant);
		if (tmp_distance < ptr_nearest->distance)
		{
			ptr_nearest->object = sphere;
			ptr_nearest->distance = tmp_distance;
		}
	}
}
