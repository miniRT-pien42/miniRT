#include "object.h"
#include "ray.h"
#include "scene.h"
#include <math.h>

static double	calc_a_for_sphere(const t_ray *ray)
{
	return (get_length(ray->direction) * get_length(ray->direction));
}

static double	calc_b_for_sphere(const t_ray *ray, t_vector v)
{
	return (2.0 * vec_dot(ray->direction, v));
}

static double	calc_c_for_sphere(const t_sphere *sphere, t_vector v)
{
	return (pow(get_length(v), 2) - pow(sphere->diameter / 2, 2));
}

double	calc_discriminant_for_sphere(\
	const t_ray *ray, const t_sphere *sphere, double *distances)
{
	const t_vector	v = vec_subtract(ray->position, sphere->center);
	const double	a = calc_a_for_sphere(ray);
	const double	b = calc_b_for_sphere(ray, v);
	const double	c = calc_c_for_sphere(sphere, v);
	const double	d = pow(b, 2) - 4 * a * c;

	calc_distance_by_discriminant(a, b, d, distances);
	return (d);
}
