#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "helpers.h"
#include "ray.h"
#include "object.h"

static bool	is_inside_sphere(t_vector pos_target, const t_sphere *sphere, t_vector ray)
{
	double	distances[2];
	double	discriminant;

	discriminant = calc_discriminant_for_sphere(\
		ray, sphere, pos_target, distances);
	if (discriminant < 0)
		return (false);//todo: ここにはこないはず。error
	if ((distances[0] > 0 && distances[1] < 0) || \
		(distances[0] < 0 && distances[1] > 0))
		return (true);
	return (false);
}

t_vector	get_normal_on_sphere(\
	t_scene *scene, t_intersection intersection, t_vector ray)
{
	t_vector		normal;
	const t_sphere	*sphere = intersection.object;
	const bool		is_inside_view = \
		is_inside_sphere(scene->camera->pos, sphere, ray);

	if (is_inside_view)
		normal = vec_normalize(vec_subtract(sphere->center, intersection.position));
	else
		normal = vec_normalize(vec_subtract(intersection.position, sphere->center));
	return (normal);
}
