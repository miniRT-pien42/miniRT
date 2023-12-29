#include "object.h"
#include "helpers.h"
#include <math.h>

static double	get_closer_distance(double discriminant, double *distances)
{
	double	closer_distance;

	if (discriminant == 0)
		closer_distance = distances[0];
	else
	{
		if (distances[0] > 0 && distances[1] > 0)
			closer_distance = fmin(distances[0], distances[1]);
		else if (fabs(distances[0]) < EPSILON && distances[1] > 0)
			closer_distance = distances[1];
		else if (fabs(distances[1]) < EPSILON && distances[0] > 0)
			closer_distance = distances[0];
		else
			closer_distance = fmax(distances[0], distances[1]);
	}
	return (closer_distance);
}

// camera,lightからの最短距離を取得。
// discriminant == 0 rayが対象に対し接線となる場合、交点を一つ持つものとして扱う
// distance == 0 rayとobjectの交点がcamera,light位置と重なる場合は数値扱いとしNaNにしない
double	get_distance_to_sphere(const t_ray *ray, t_sphere *sphere)
{
	double		distances[2];
	double		discriminant;
	double		distance;

	discriminant = calc_discriminant_for_sphere(ray, sphere, distances);
	if (discriminant < 0)
		return (NAN);
	distance = get_closer_distance(discriminant, distances);
	if (distance < 0)
		return (NAN);
	return (distance);
}
