#include "object.h"
#include "ray.h"
#include "scene.h"
#include <math.h>

// pa:        交点位置
// pa_normal: paからの法線ベクトル
// 中心軸上での法線とpaから求めた法線が同じ方向を向いていてheight以内かどうかを返す
bool	is_intersect_cylinder(\
				const t_ray *ray, const t_cylinder *cylinder, double distance)
{
	const t_vector	pa = vec_add(\
		ray->position, vec_scalar(ray->direction, distance));
	const t_vector	pa_normal = vec_subtract(pa, cylinder->center);
	const double	height = vec_dot(cylinder->normal, pa_normal);

	return (-cylinder->height / 2 <= height && height <= cylinder->height / 2);
}

// discriminant >= 0 かつ交点の高さがcylinder.height以下なら衝突している
double	get_distance_to_cylinder(\
				t_vector ray_direction, t_vector pos, t_cylinder *cylinder)
{
	double		distances[2];
	double		discriminant;
	const t_ray	ray = (t_ray){.position = pos, .direction = ray_direction};
	double		outside;
	double		inside;

	discriminant = calc_discriminant_for_cylinder(&ray, cylinder, distances);
	if (discriminant < 0)
		return (NAN);
	outside = fmin(distances[0], distances[1]);
	if (is_intersect_cylinder(&ray, cylinder, outside) && outside > 0)
		return (outside);
	inside = fmax(distances[0], distances[1]);
	if (is_intersect_cylinder(&ray, cylinder, inside) && inside > 0)
		return (inside);
	return (NAN);
}
