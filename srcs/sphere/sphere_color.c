#include "object.h"
#include "ray.h"

static bool	is_inside_sphere(const t_sphere *sphere, const t_ray *ray)
{
	double	distances[2];

	calc_discriminant_for_sphere(ray, sphere, distances);
	if (has_negative_distance(distances))
		return (true);
	return (false);
}

t_vector	get_normal_on_sphere(t_intersection intersection, const t_ray *ray)
{
	t_vector		normal;
	const t_sphere	*sphere = intersection.object;
	const bool		is_inside_view = is_inside_sphere(sphere, ray);

	if (is_inside_view)
	{
		normal = vec_normalize(\
			vec_subtract(sphere->center, intersection.position));
	}
	else
	{
		normal = vec_normalize(\
			vec_subtract(intersection.position, sphere->center));
	}
	return (normal);
}
