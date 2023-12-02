#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "helpers.h"
#include "ray.h"

// 解の方程式
t_discriminant	calc_discriminant(\
		const t_vector ray, const t_vector camera_pos, const t_sphere *sphere)
{
	t_discriminant	discriminant;
	const t_vector	v = vec_subtract(camera_pos, sphere->center);

	discriminant.a = pow(get_length(ray), 2);
	discriminant.b = 2.0 * vec_dot(ray, v);
	discriminant.c = pow(get_length(v), 2) - pow(sphere->diameter / 2, 2);
	discriminant.d = pow(discriminant.b, 2) - \
		4 * discriminant.a * discriminant.c;
	return (discriminant);
}

// objectへの距離取得。ray逆方向は-1をreturnして判定で弾けるようにする
static double	get_valid_distance(double a, double b, bool *ptr_is_inside)
{
	if (a * b < 0)
	{
		if (ptr_is_inside != NULL && !*ptr_is_inside)
			*ptr_is_inside = true;
		return (fmax(a, b));
	}
	else if (a < 0 && b < 0)
		return (NO_INTERSECTION);
	return (fmin(a, b));
}

// rayとsphereとの距離。sphareの内部にcameraがある場合は，sphere->is_camera_insideをtrueにしておく
double	calc_distance_to_object(\
	t_discriminant discriminant, bool *is_inside, bool is_abs)
{
	const double	num_bottom = 2.0 * discriminant.a;
	const double	num_top1 = -1 * discriminant.b;
	const double	num_top2 = sqrt(discriminant.d);
	double			distance1;
	double			distance2;

	if (discriminant.d == 0)
		return (num_top1 / num_bottom);
	distance1 = (num_top1 + num_top2) / num_bottom;
	distance2 = (num_top1 - num_top2) / num_bottom;
	if (is_abs)
		return (fmin(fabs(distance1), fabs(distance2)));
	else
		return (get_valid_distance(distance1, distance2, is_inside));
}

// cameraからのrayとsphereとの衝突判定。衝突していればtrueを返す。
bool	is_intersect_to_sphere(const double d)
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
		tmp_distance = calc_distance_to_object(\
			discriminant, &sphere->is_camera_inside, false);
		if (tmp_distance < ptr_nearest->distance)
		{
			ptr_nearest->object = sphere;
			ptr_nearest->distance = tmp_distance;
		}
	}
}
