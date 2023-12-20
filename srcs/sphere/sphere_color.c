#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "helpers.h"
#include "ray.h"

t_vector	get_normal_on_sphere(\
	t_vector position, t_sphere *sphere, bool is_camera_inside)
{
	t_vector	normal;

	if (is_camera_inside)
	{
		normal = vec_normalize(\
			vec_subtract(sphere->center, position));
	}
	else
	{
		normal = vec_normalize(\
			vec_subtract(position, sphere->center));
	}
	return (normal);
}

bool	is_inside_sphere(t_vector pos_target, t_sphere *sphere, t_vector ray)
{
	double	distances[2];
	double	discriminant;

	discriminant = calc_discriminant_for_sphere(\
		ray, sphere, pos_target, distances);
	if (discriminant < 0)
		return (NAN);
	if ((distances[0] > 0 && distances[1] < 0) || \
		(distances[0] < 0 && distances[1] > 0))
		return (true);
	return (false);
}
