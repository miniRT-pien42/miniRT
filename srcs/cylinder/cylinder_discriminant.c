#include "object.h"
#include "ray.h"
#include <math.h>

static double	calc_a_for_cylinder(const t_ray *ray, t_cylinder *cylinder)
{
	double	a;

	a = vec_length(vec_cross(ray->direction, cylinder->normal));
	return (a * a);
}

static double	calc_b_for_cylinder(const t_ray *ray, t_cylinder *cylinder)
{
	double	b;

	b = 2 * vec_dot(vec_cross(ray->direction, cylinder->normal), \
					vec_cross(vec_subtract(\
					ray->position, cylinder->center), cylinder->normal));
	return (b);
}

static double	calc_c_for_cylinder(const t_ray *ray, t_cylinder *cylinder)
{
	double			c;
	const double	cylinder_r = cylinder->diameter / 2;

	c = vec_length(vec_cross(vec_subtract(\
		ray->position, cylinder->center), cylinder->normal));
	return (c * c - cylinder_r * cylinder_r);
}

double	calc_discriminant_for_cylinder(\
					const t_ray *ray, t_cylinder *cylinder, double *distances)
{
	const double	a = calc_a_for_cylinder(ray, cylinder);
	const double	b = calc_b_for_cylinder(ray, cylinder);
	const double	c = calc_c_for_cylinder(ray, cylinder);
	const double	d = b * b - 4 * a * c;

	calc_distance_by_discriminant(a, b, d, distances);
	return (d);
}
