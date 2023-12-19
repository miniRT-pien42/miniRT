#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "helpers.h"
#include "object.h"
#include "ray.h"

double	get_distance_to_plane(t_vector ray, t_scene *scene, t_plane *plane)
{
	double	num_bottom;
	double	num_top;
	double	distance;

	num_bottom = vec_dot(ray, plane->dir_n);
	if (num_bottom == 0)
		return (NAN);
	num_top = \
		vec_dot(vec_subtract(scene->camera->pos, plane->point), plane->dir_n);
	distance = num_top / num_bottom * -1;
	if (distance <= 0)
		return (NAN);
	return (distance);
}
