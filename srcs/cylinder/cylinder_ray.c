#include <math.h>
#include "ray.h"
#include "scene.h"

static double	calc_a_for_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	double	a;

	a = vec_norm(vec_cross(ray->direction, cylinder->normal));
	return (a * a);
}

static double	calc_b_for_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	double	b;

	b = 2 * vec_dot(vec_cross(ray->direction, cylinder->normal), \
					vec_cross(vec_subtract(ray->position, cylinder->center), cylinder->normal));
	return (b);
}

static double	calc_c_for_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	double			c;
	const double	cylinder_r = cylinder->diameter / 2;

	c = vec_norm(vec_cross(vec_subtract(ray->position, cylinder->center), cylinder->normal));
	return (c * c - cylinder_r * cylinder_r);
}

static double	calc_discriminant_for_cylinder(\
							t_ray *ray, t_cylinder *cylinder, double *distances)
{
	const double	a = calc_a_for_cylinder(ray, cylinder);
	const double	b = calc_b_for_cylinder(ray, cylinder);
	const double	c = calc_c_for_cylinder(ray, cylinder);
	const double	d = b * b - 4 * a * c;

	calc_distance_by_discriminant(a, b, d, distances);
	return (d);
}

// pa:        交点位置
// pa_normal: paからの法線ベクトル
// 中心軸上での法線とpaから求めた法線が同じ方向を向いていてheight以内かどうかを返す
static bool	is_within_cylinder_height(\
					t_ray *ray, t_cylinder *cylinder, double distance)
{
	const t_vector	pa = vec_add(ray->position, vec_scalar(ray->direction, distance));
	const t_vector	pa_normal = vec_subtract(pa, cylinder->center);
	const double	height = vec_dot(cylinder->normal, pa_normal);

	return (0 <= height && height <= cylinder->height);
}

// discriminant >= 0 かつ is_within_cylinder_height() == true なら衝突している
double	get_distance_to_cylinder(\
				t_vector ray_direction, t_scene *scene, t_cylinder *cylinder)
{
	double	distances[2];
	double	discriminant;
	t_ray	ray = (t_ray){.position = scene->camera->pos, .direction = ray_direction};
	double	distance;

	discriminant = calc_discriminant_for_cylinder(&ray, cylinder, distances);
	if (discriminant < 0)
		return (NAN);
	distance = get_closer_distance(discriminant, distances);
	if (distance <= 0)
		return (NAN);
	if (is_within_cylinder_height(&ray, cylinder, distance))
		return (distance);
	return (NAN);
}
