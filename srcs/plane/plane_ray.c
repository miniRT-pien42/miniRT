#include "object.h"
#include "ray.h"
#include "scene.h"
#include <math.h>

double	get_distance_to_plane(const t_ray *ray, t_vector pos, t_plane *plane)
{
	double	num_bottom;
	double	num_top;
	double	distance;

	num_bottom = vec_dot(ray->direction, plane->normal);
	if (num_bottom == 0)
		return (NAN);
	num_top = \
		vec_dot(vec_subtract(pos, plane->point), plane->normal);
	distance = num_top / num_bottom * -1;
	if (distance < 0)
		return (NAN);
	return (distance);
}
