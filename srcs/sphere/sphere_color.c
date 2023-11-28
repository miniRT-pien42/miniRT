#include <stdlib.h>
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

// shadow-rayとsphereとの衝突判定。衝突していればtrueを返す=>その画素は影
bool	is_shadow_by_sphere(const t_vector shadow_ray,
							const t_scene *scene, const t_sphere *sphere_target)
{
	t_discriminant	discriminant_target;
	t_discriminant	discriminant;
	t_sphere		*sphere_current;
	double			tmp_distance;
	double			distance_target;

	sphere_current = scene->list_sphere;
	discriminant_target = calc_discriminant(\
							shadow_ray, scene->light->pos, sphere_target);
	distance_target = calc_distance_to_object(discriminant_target, NULL);
	while (sphere_current)
	{
		discriminant = calc_discriminant(\
							shadow_ray, scene->light->pos, sphere_current);
		if (is_intersect_to_sphere(discriminant.d))
		{
			tmp_distance = calc_distance_to_object(discriminant, NULL);
			if (tmp_distance < distance_target)
				return (true);
		}
		sphere_current = sphere_current->next;
	}
	return (false);
}
