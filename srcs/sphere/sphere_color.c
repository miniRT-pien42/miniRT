#include "vector.h"
#include "display.h"
#include "scene.h"
#include "helpers.h"
#include "ray.h"
#include "object.h"
#include "error.h"
#include <stdlib.h>
#include <math.h>

static bool	is_inside_sphere(const t_sphere *sphere, const t_ray *ray)
{
	double	distances[2];
	double	discriminant;

	discriminant = calc_discriminant_for_sphere(ray, sphere, distances);
	if (discriminant < 0)
		error_exit(ERR_INTERSECTION);
	if (is_has_negative_distance(distances))
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
