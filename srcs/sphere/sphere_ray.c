#include "object.h"
#include "ray.h"

static double	calc_a_for_sphere(const t_ray *ray)
{
	return (vec_length(ray->direction) * vec_length(ray->direction));
}

static double	calc_b_for_sphere(const t_ray *ray, t_vector v)
{
	return (2.0 * vec_dot(ray->direction, v));
}

static double	calc_c_for_sphere(const t_sphere *sphere, t_vector v)
{
	const double	len = vec_length(v);
	const double	radius = sphere->diameter / 2;

	return (len * len - radius * radius);
}

double	calc_discriminant_for_sphere(\
	const t_ray *ray, const t_sphere *sphere, double *distances)
{
	const t_vector	v = vec_subtract(ray->position, sphere->center);
	const double	a = calc_a_for_sphere(ray);
	const double	b = calc_b_for_sphere(ray, v);
	const double	c = calc_c_for_sphere(sphere, v);
	const double	d = b * b - 4 * a * c;

	calc_distance_by_discriminant(a, b, d, distances);
	return (d);
}
