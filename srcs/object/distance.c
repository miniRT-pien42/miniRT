#include "helpers.h"
#include <math.h>

void	calc_distance_by_discriminant(\
	const double a, const double b, const double d, double *distances)
{
	if (d < 0)
		return ;
	else if (d == 0)
	{
		distances[0] = -b / (2 * a);
		distances[1] = -b / (2 * a);
	}
	else
	{
		distances[0] = (-b - sqrt(d)) / (2 * a);
		distances[1] = (-b + sqrt(d)) / (2 * a);
	}
}

double	get_closer_distance(double discriminant, double *distances)
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
