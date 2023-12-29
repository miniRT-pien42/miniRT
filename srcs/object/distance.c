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

bool	is_has_negative_distance(double *distances)
{
	if ((distances[0] > 0 && distances[1] < 0) || \
		(distances[0] < 0 && distances[1] > 0) || \
		(fabs(distances[0]) < EPSILON && distances[1] > 0) || \
		(fabs(distances[1]) < EPSILON && distances[0] > 0))
		return (true);
	return (false);
}
