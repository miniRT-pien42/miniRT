#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "helpers.h"
#include "ray.h"

static double	calc_a_for_sphere(t_vector ray)
{
	return (pow(get_scalar(ray), 2));
}

static double	calc_b_for_sphere(t_vector ray, t_vector v)
{
	return (2.0 * vec_dot(ray, v));
}

static double	calc_c_for_sphere(t_sphere *sphere, t_vector v)
{
	return (pow(get_scalar(v), 2) - pow(sphere->diameter / 2, 2));
}

double	calc_discriminant_for_sphere(\
	t_vector ray, t_sphere *sphere, t_vector camera_pos, double *distances)
{
	const t_vector	v = vec_subtract(camera_pos, sphere->center);
	const double	a = calc_a_for_sphere(ray);
	const double	b = calc_b_for_sphere(ray, v);
	const double	c = calc_c_for_sphere(sphere, v);
	const double	d = pow(b, 2) - 4 * a * c;

	calc_distance_by_discriminant(a, b, d, distances);
	return (d);
}
//カメラから見える最短距離を取得
double	get_distance_to_sphere(t_vector ray, t_vector pos, t_sphere *sphere)
{
	double	distances[2];
	double	discriminant;
	double	distance;

	discriminant = calc_discriminant_for_sphere(\
		ray, sphere, pos, distances);
	if (discriminant < 0)
		return (NAN);
	distance = get_closer_distance(discriminant, distances);
	if (distance <= 0)
		return (NAN);
	return (distance);
}
