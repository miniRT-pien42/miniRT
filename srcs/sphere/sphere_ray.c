#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "utils.h"
#include "ray.h"

// 解の方程式
t_discriminant	calc_discriminant(\
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

// objectへの距離取得。ray逆方向は-1をreturnして判定で弾けるようにする
double	get_valid_distance(double a, double b, bool *ptr_is_inside)
{
	if (a * b < 0)
	{
		if (!*ptr_is_inside)
			*ptr_is_inside = true;
		return (fmax(a, b));
	}
	else if (a < 0 && b < 0)
		return (-1);
	return (fmin(a, b));
}

// rayとsphereとの距離。sphareの内部にcameraがある場合は，sphere->is_camera_insideをtrueにしておく
double	calc_distance_to_object(\
	t_discriminant discriminant, bool *is_inside)
{
	const double	num_bottom = 2.0 * discriminant.a;
	const double	num_top1 = -1 * discriminant.b;
	const double	num_top2 = sqrt(discriminant.d);

	if (discriminant.d == 0)
		return (num_top1 / num_bottom);
	return (get_valid_distance(\
				(num_top1 + num_top2) / num_bottom, \
				(num_top1 - num_top2) / num_bottom, \
				is_inside));
}

// cameraからのrayとsphereとの衝突判定。衝突していればtrueを返す。
bool	is_intersect_to_sphere(const double d)
{
	return (d >= 0);
}

t_intersection	get_nearest_object(t_vector ray, t_scene *scene)
{
	t_intersection	nearest;
	t_discriminant	discriminant;
	t_sphere		*sphere_current;
	double			tmp_distance;

	nearest.distance = INFINITY;
	sphere_current = scene->list_sphere;
	while (sphere_current)
	{
		discriminant = calc_discriminant(\
							ray, scene->camera->pos, sphere_current);
		if (is_intersect_to_sphere(discriminant.d))
		{
			tmp_distance = calc_distance_to_object(\
				discriminant, &sphere_current->is_camera_inside);
			if (tmp_distance >= 0 && tmp_distance < nearest.distance)
			{
				nearest.sphere = sphere_current;
				nearest.distance = tmp_distance;
			}
		}
		sphere_current = sphere_current->next;
	}
	return (nearest);
}

// shadow-rayとsphereとの衝突判定。衝突していればtrueを返す=>その画素は影
// lightが自分の内側にあるかの判定は？
bool	is_shadow_by_sphere(const t_vector shadow_ray,
			const t_scene *scene, const t_sphere *sphere_target)
{
	t_discriminant	discriminant_target;
	t_discriminant	discriminant;
	t_sphere		*sphere_current;

	sphere_current = scene->list_sphere;
	discriminant_target = calc_discriminant(\
							shadow_ray, scene->light->pos, sphere_target);
	while (sphere_current)
	{
		discriminant = calc_discriminant(\
							shadow_ray, scene->light->pos, sphere_current);
		if (discriminant.d > 0 && discriminant.d < discriminant_target.d)
			return (true);
		sphere_current = sphere_current->next;
	}
	return (false);
}
