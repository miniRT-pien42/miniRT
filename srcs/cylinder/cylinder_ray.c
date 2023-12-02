#include <math.h>
#include "ray.h"
#include "scene.h"

static double	calc_a_for_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	double	a;

	a = vec_norm(vec_cross(ray->direction, cylinder->axis_normal));
	return (a * a);
}

static double	calc_b_for_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	double	b;

	b = 2 * vec_dot(vec_cross(ray->direction, cylinder->axis_normal), \
					vec_cross(vec_subtract(ray->position, cylinder->center), cylinder->axis_normal));
	return (b);
}

static double	calc_c_for_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	double			c;
	const double	cylinder_r = cylinder->diameter / 2;

	c = vec_norm(vec_cross(vec_subtract(ray->position, cylinder->center), cylinder->axis_normal));
	return (c * c - cylinder_r * cylinder_r);
}

// 共通して使えそう
static void	calc_distance_by_discriminant(\
	const double a, const double b, const double d, double *distance)
{
	if (d < 0)
		return ;
	else if (d == 0)
	{
		distance[0] = -b / (2 * a);
		distance[1] = -b / (2 * a);
	}
	else
	{
		distance[0] = (-b - sqrt(d)) / (2 * a);
		distance[1] = (-b + sqrt(d)) / (2 * a);
	}
}

static double	calc_discriminant_for_cylinder(\
							t_ray *ray, t_cylinder *cylinder, double *distance)
{
	const double	a = calc_a_for_cylinder(ray, cylinder);
	const double	b = calc_b_for_cylinder(ray, cylinder);
	const double	c = calc_c_for_cylinder(ray, cylinder);
	const double	d = b * b - 4 * a * c;

	calc_distance_by_discriminant(a, b, d, distance);
	return (d);
}

static double	get_clother_distance(double discriminant, double *distance)
{
	double	clother_distance;

	if (discriminant == 0)
		clother_distance = distance[0];
	else
	{
		if (distance[0] >= 0 && distance[1] >= 0)
			clother_distance = fmin(distance[0], distance[1]);
		else
			clother_distance = fmax(distance[0], distance[1]);
	}
	return (clother_distance);
}

// pa:        交点位置
// pa_normal: paからの法線ベクトル
// 中心軸上での法線とpaから求めた法線が同じ方向を向いていてheight以内かどうかを返す
static bool	is_within_cylinder_height(\
					t_ray *ray, t_cylinder *cylinder, double clother_distance)
{
	const t_vector	pa = vec_add(ray->position, vec_scalar(ray->direction, clother_distance));
	const t_vector	pa_normal = vec_subtract(pa, cylinder->center);
	const double	height = vec_dot(cylinder->axis_normal, pa_normal);

	return (0 <= height && height <= cylinder->height);
}

// discriminant >= 0 かつ is_within_cylinder_height() == true なら衝突している
double	get_clother_distance_to_cylinder(\
				t_vector ray_direction, t_scene *scene, t_cylinder *cylinder)
{
	double	distance[2];
	double	discriminant;
	t_ray	ray = (t_ray){.position = scene->camera->pos, .direction = ray_direction};
	double	clother_distance;

	discriminant = calc_discriminant_for_cylinder(&ray, cylinder, distance);
	if (discriminant < 0)
		return (NAN);
	clother_distance = get_clother_distance(discriminant, distance);
	if (clother_distance <= 0)
		return (NAN);
	if (is_within_cylinder_height(&ray, cylinder, clother_distance))
		return (clother_distance);
	return (NAN);
}
