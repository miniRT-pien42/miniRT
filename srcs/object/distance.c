#include <math.h>
#include "ray.h"
#include "scene.h"

// 共通して使えそう
void	calc_distance_by_discriminant(\
	const double a, const double b, const double d, double *list_distance)
{
	if (d < 0)
		return ;
	else if (d == 0)
	{
		list_distance[0] = -b / (2 * a);
		list_distance[1] = -b / (2 * a);
	}
	else
	{
		list_distance[0] = (-b - sqrt(d)) / (2 * a);
		list_distance[1] = (-b + sqrt(d)) / (2 * a);
	}
}

double	get_closer_distance(double discriminant, double *list_distance)
{
	double	closer_distance;

	if (discriminant == 0)
		closer_distance = list_distance[0];
	else
	{
		if (list_distance[0] >= 0 && list_distance[1] >= 0)
			closer_distance = fmin(list_distance[0], list_distance[1]);
		else
			closer_distance = fmax(list_distance[0], list_distance[1]);
	}
	return (closer_distance);
}
