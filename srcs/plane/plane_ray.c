#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "utils.h"
#include "ray.h"

void	judge_nearest_plane(\
	t_vector ray, t_scene *scene, t_plane *plane, t_intersection *ptr_nearest)
{
	double	num_bottom;
	double	tmp_distance;

	num_bottom = vec_dot(ray, plane->dir_n);
	if (num_bottom == 0)
		return ;
	tmp_distance = \
		vec_dot(vec_subtract(scene->camera->pos, plane->point), \
		plane->dir_n) / num_bottom * -1;
	if (tmp_distance > 0 && tmp_distance < ptr_nearest->distance)
	{
		ptr_nearest->object = plane;
		ptr_nearest->distance = tmp_distance;
	}
}
