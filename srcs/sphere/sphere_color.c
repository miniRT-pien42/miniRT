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
	t_sphere		*sphere;
	t_discriminant	discriminant;

	sphere = ptr_nearest->object;
	discriminant = calc_discriminant(\
		vec_subtract(ptr_nearest->position, scene->light->pos), \
		scene->light->pos, sphere);
	if (is_intersect_to_sphere(discriminant.d))
	{
		calc_distance_to_object(discriminant);
	}
}

// shadow-rayとsphereとの衝突判定。衝突していればtrueを返す=>その画素は影
// sphere_targetは、影を落とされるかチェックする対象の球体
bool	is_shadow_by_sphere(const t_vector shadow_ray,
							const t_scene *scene, const t_sphere *sphere_target)
{
	t_discriminant	discriminant_target;
	t_discriminant	discriminant;
	t_deque_node	*object_current;
	double			tmp_distance;
	double			distance_target;

	object_current = scene->list_object->node;
	discriminant_target = calc_discriminant(\
							shadow_ray, scene->light->pos, sphere_target);
	distance_target = calc_distance_to_object_abs(discriminant_target);
	while (object_current)
	{
		if (get_object_type(object_current->content) == SPHERE)
		{
			discriminant = calc_discriminant(\
				shadow_ray, scene->light->pos, object_current->content);
			if (is_intersect_to_sphere(discriminant.d))
			{
				//rayとの交点がある場合、その交点までの距離を計算
				tmp_distance = \
					calc_distance_to_object_abs(discriminant);
				if (tmp_distance < distance_target)
					return (true);
			}
		}
		object_current = object_current->next;
	}
	return (false);
}
