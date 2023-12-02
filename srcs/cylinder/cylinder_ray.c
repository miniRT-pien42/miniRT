#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "display.h"
#include "object.h"
#include "helpers.h"
#include "ray.h"
#include "scene.h"

// 中心軸上での交差判定
static t_discriminant	calc_discriminant_for_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_discriminant	discriminant;
	double			a;
	double			b;
	double			c;

	a = vec_norm(vec_cross(ray->direction, cylinder->axis_normal));
	a *= a;
	b = 2 * vec_dot(vec_cross(ray->direction, cylinder->axis_normal), \
					vec_cross(vec_subtract(ray->position, cylinder->center), cylinder->axis_normal));
	c = vec_norm(vec_cross(vec_subtract(ray->position, cylinder->center), cylinder->axis_normal));
	c = pow(c, 2) - pow(cylinder->diameter / 2, 2);
	discriminant.a = a;
	discriminant.b = b;
	discriminant.c = c;
	discriminant.d = b * b - 4 * a * c;
	return (discriminant);
}

static bool	is_intersect_cylinder(t_discriminant *discriminant, \
						t_ray *ray, t_cylinder *cylinder, double *tmp_distance)
{
	double	t1;
	double	t2;

	// 交差しない
	if (discriminant->d < 0)
		return (false);
	if (discriminant->d == 0)
		*tmp_distance = -discriminant->b / (2 * discriminant->a);
	else
	{
		// rayとcylinderの距離(円柱の内側と外側)
		t1 = (-discriminant->b - sqrt(discriminant->d)) / (2 * discriminant->a);
		t2 = (-discriminant->b + sqrt(discriminant->d)) / (2 * discriminant->a);
		*tmp_distance = (t1 > 0 && t2 > 0) ? fmin(t1, t2) : fmax(t1, t2);
	}

	if (*tmp_distance > 0)
	{
		// 交点位置pa
		const t_vector	pa = vec_add(ray->position, vec_scalar(ray->direction, *tmp_distance));
		// paからの法線ベクトル
		const t_vector	pa_normal = vec_subtract(pa, cylinder->center);
		// 中心軸上での法線とpaから求めた法線が同じ方向を向いていてheight以内かどうか
		const double	height = vec_dot(cylinder->axis_normal, pa_normal);
		if (0 <= height && height <= cylinder->height)
			return (true);
	}
	// 交差しない
	return (false);
}

void	update_nearest_cylinder(t_vector ray_direction, \
			t_scene *scene, t_cylinder *cylinder, t_intersection *ptr_nearest)
{
	t_discriminant	discriminant;
	double			tmp_distance;
	t_ray			ray = (t_ray){.position = scene->camera->pos, .direction = ray_direction};

	discriminant = calc_discriminant_for_cylinder(&ray, cylinder);
	if (is_intersect_cylinder(&discriminant, &ray, cylinder, &tmp_distance))
	{
		// tmp_distance = calc_distance_to_object(discriminant);
		if (tmp_distance < ptr_nearest->distance)
		{
			ptr_nearest->object = cylinder;
			ptr_nearest->distance = tmp_distance;
		}
	}
}
