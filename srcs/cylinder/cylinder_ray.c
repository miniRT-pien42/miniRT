#include "object.h"
#include "ray.h"
#include "scene.h"
#include <math.h>

static double	calc_a_for_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	double	a;

	a = get_length(vec_cross(ray->direction, cylinder->normal));
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

	c = get_length(vec_cross(vec_subtract(ray->position, cylinder->center), cylinder->normal));
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
static bool	is_intersect_cylinder(\
					t_ray *ray, t_cylinder *cylinder, double distance)
{
	const t_vector	pa = vec_add(ray->position, vec_scalar(ray->direction, distance));
	const t_vector	pa_normal = vec_subtract(pa, cylinder->center);
	const double	height = vec_dot(cylinder->normal, pa_normal);

	return (0 <= height && height <= cylinder->height);
}

// discriminant >= 0 かつ交点の高さがcylinder.height以下なら衝突している
double	get_distance_to_cylinder(\
				t_vector ray_direction, t_scene *scene, t_cylinder *cylinder)
{
	double	distances[2];
	double	discriminant;
	t_ray	ray = (t_ray){.position = scene->camera->pos, .direction = ray_direction};
	double	outside;
	double	inside;

	discriminant = calc_discriminant_for_cylinder(&ray, cylinder, distances);
	if (discriminant < 0)
		return (NAN);
	outside = fmin(distances[0], distances[1]);
	if (is_intersect_cylinder(&ray, cylinder, outside))
		return (outside);
	inside = fmax(distances[0], distances[1]);
	if (is_intersect_cylinder(&ray, cylinder, inside))
		return (inside);
	return (NAN);
}
