#include <math.h>
#include "ray.h"
#include "scene.h"

// 共通して使えそう
void	calc_distance_by_discriminant(\
	const double a, const double b, const double d, double *distance)
{
	if (d < 0)
		return ;
	else if (d == 0)
	{
		distance[0] = -b / (2 * a);
		distance[1] = -b / (2 * a);
	}
	else
	{
		distance[0] = (-b - sqrt(d)) / (2 * a);
		distance[1] = (-b + sqrt(d)) / (2 * a);
	}
}

double	get_closer_distance(double discriminant, double *distance)
{
	double	clother_distance;

	if (discriminant == 0)
		clother_distance = distance[0];
	else
	{
		if (distance[0] >= 0 && distance[1] >= 0)
			clother_distance = fmin(distance[0], distance[1]);
		else
			clother_distance = fmax(distance[0], distance[1]);
	}
	return (clother_distance);
}