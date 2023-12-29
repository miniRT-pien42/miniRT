#include "object.h"
#include "ray.h"
#include "scene.h"
#include <math.h>

double	get_distance_to_plane(const t_ray *ray, t_plane *plane)
{
	double	denom;
	double	numer;
	double	distance;

	denom = vec_dot(ray->direction, plane->normal);
	if (denom == 0)
		return (NAN);
	numer = \
		vec_dot(vec_subtract(ray->position, plane->point), plane->normal);
	distance = numer / denom * -1;
	if (distance < 0)
		return (NAN);
	return (distance);
}
