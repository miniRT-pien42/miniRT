#include "object.h"
#include "ray.h"

t_vector	get_normal_on_plane(t_plane *plane, const t_ray *ray)
{
	t_vector	normal;

	normal = plane->normal;
	if (vec_dot(normal, vec_normalize(ray->direction)) > 0)
		normal = vec_scalar(normal, -1);
	return (normal);
}
