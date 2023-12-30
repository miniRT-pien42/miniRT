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
		else
			closer_distance = fmax(distances[0], distances[1]);
	}
	return (closer_distance);
}

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
