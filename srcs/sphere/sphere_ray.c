#include "object.h"
#include "scene.h"
#include <math.h>

static double	calc_a_for_sphere(t_vector ray)
{
	return (pow(get_length(ray), 2));
}

static double	calc_b_for_sphere(t_vector ray, t_vector v)
{
	return (2.0 * vec_dot(ray, v));
}

static double	calc_c_for_sphere(const t_sphere *sphere, t_vector v)
{
	return (pow(get_length(v), 2) - pow(sphere->diameter / 2, 2));
}

double	calc_discriminant_for_sphere(\
	t_vector ray, const t_sphere *sphere, t_vector pos, double *distances)
{
	const t_vector	v = vec_subtract(pos, sphere->center);
	const double	a = calc_a_for_sphere(ray);
	const double	b = calc_b_for_sphere(ray, v);
	const double	c = calc_c_for_sphere(sphere, v);
	const double	d = pow(b, 2) - 4 * a * c;

	calc_distance_by_discriminant(a, b, d, distances);
	return (d);
}

// camera,lightからの最短距離を取得。
// discriminant == 0 rayが対象に対し接線となる場合、交点を一つ持つものとして扱う
// distance == 0 rayとobjectの交点がcamera,light位置と重なる場合は数値扱いとしNaNにしない
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
	if (distance < 0)
		return (NAN);
	return (distance);
}
