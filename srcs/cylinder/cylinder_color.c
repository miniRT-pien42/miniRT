#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "helpers.h"
#include "ray.h"

static t_vector	vec_center_pos(t_intersection intersection)
{
	const t_cylinder	*cylinder = intersection.object;
	t_vector	center_this_height;
	const double distance_to_center = \
		get_length(vec_subtract(cylinder->center, intersection.position));
	double		height_to_center = \
		sqrt(distance_to_center * distance_to_center - (cylinder->diameter / 2) * (cylinder->diameter / 2));

	center_this_height = vec_add(cylinder->center, vec_scalar(cylinder->normal, height_to_center));
	return (center_this_height);
}

//カメラray、交点=>シリンダ中心のベクトルから内積を求めて、内外判定
t_vector	get_normal_on_cylinder(\
	t_scene *scene, t_intersection intersection, t_vector ray)
{
	(void)scene;
	t_vector			normal;
	const t_cylinder	*cylinder = intersection.object;
	double				dot_cy;
	t_vector	center_this_height = vec_center_pos(intersection);

	normal = vec_subtract(intersection.position, cylinder->center);
	dot_cy = vec_dot(normal, ray);
	if (0 <= dot_cy)
	{
		normal = vec_normalize(\
			vec_subtract(intersection.position, center_this_height));
	}
	else
	{
		normal = vec_normalize(\
			vec_subtract(center_this_height, intersection.position));
	}
	return (normal);
}

bool	is_inside_cylinder(t_vector pos_target, t_cylinder *cylinder, t_vector ray)
{
	double	distances[2];
	double	discriminant;

	t_ray	ray_d = (t_ray){.position = pos_target, .direction = ray};
	discriminant = calc_discriminant_for_cylinder(\
		&ray_d, cylinder, distances);
	if (discriminant < 0)
		return (false);
	if ((is_intersect_cylinder(&ray_d, cylinder, distances[0])) || \
		(is_intersect_cylinder(&ray_d, cylinder, distances[1])))
		return (true);
	return (false);
}
