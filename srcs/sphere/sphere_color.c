#include <math.h>
#include "vector.h"
#include "ray.h"
#include "object.h"
#include "color.h"

int	convert_rgb(t_rgb color)
{
	return ((color.r << RED_SHIFT) | (color.g << GREEN_SHIFT) | color.b);
}

//rayはlight->posを通ればなんでもよい。
void	check_light_inside_sphere(\
	const t_scene *scene, t_intersection *ptr_nearest)
{
	const t_discriminant	discriminant = calc_discriminant(\
		vec_subtract(ptr_nearest->position, scene->light->pos), \
		scene->light->pos, ptr_nearest->sphere);

	if (is_intersect_to_sphere(discriminant.d))
	{
		calc_distance_to_object(\
			discriminant, &ptr_nearest->sphere->is_light_inside);
	}
}