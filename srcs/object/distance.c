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
