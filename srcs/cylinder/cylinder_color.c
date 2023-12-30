#include "helpers.h"
#include "object.h"
#include "ray.h"
#include "vector.h"
#include <math.h>

bool	is_cylinder_self_shadow(\
	t_cylinder *cylinder, const t_ray *ray_shadow)
{
	double		distances[2];
	double		distance_min;
	double		discriminant;

	discriminant = \
		calc_discriminant_for_cylinder(ray_shadow, cylinder, distances);
	if (discriminant == 0)
		return (false);
	distance_min = fmin(distances[0], distances[1]);
	if (distance_min < (1.0 - EPSILON) && distance_min > EPSILON && \
		is_intersect_cylinder(ray_shadow, cylinder, distance_min))
		return (true);
	return (false);
}

static t_vector	nearest_pos_on_axis(t_vector pos, const t_cylinder *cylinder)
{
	const t_vector	ap = vec_subtract(cylinder->center, pos);
	const double	height = vec_dot(cylinder->normal, ap);

	return (vec_add(cylinder->center, vec_scalar(cylinder->normal, -height)));
}

static bool	is_camera_inside_cylinder(\
	t_cylinder *cylinder, const t_ray *ray_shadow)
{
	double		distances[2];

	calc_discriminant_for_cylinder(ray_shadow, cylinder, distances);
	if (has_negative_distance(distances))
		return (true);
	if (is_intersect_cylinder(\
		ray_shadow, cylinder, fmin(distances[0], distances[1])))
		return (false);
	if (is_intersect_cylinder(\
		ray_shadow, cylinder, fmax(distances[0], distances[1])))
		return (true);
	return (false);
}

t_vector	get_normal_on_cylinder(\
	t_intersection intersection, const t_ray *ray)
{
	t_vector	normal;
	t_cylinder	*cylinder;
	bool		is_inside_view;
	t_vector	np;

	cylinder = intersection.object;
	is_inside_view = is_camera_inside_cylinder(cylinder, ray);
	np = nearest_pos_on_axis(intersection.position, cylinder);
	if (is_inside_view)
		normal = vec_normalize(vec_subtract(np, intersection.position));
	else
		normal = vec_normalize(vec_subtract(intersection.position, np));
	return (normal);
}
