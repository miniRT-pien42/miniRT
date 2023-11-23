#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "utils.h"
#include "ray.h"

// 解の方程式
static t_discriminant	*calc_discriminant(\
		const t_vector ray, t_camera *camera, t_sphere *sphere)
{
	t_discriminant	*discriminant;
	const t_vector	v = vec_subtract(camera->pos, sphere->center);

	discriminant = (t_discriminant *)malloc(sizeof(t_discriminant));
	if (discriminant == NULL)
		return (NULL);
	discriminant->a = pow(get_scalar(ray), 2);
	discriminant->b = 2.0 * vec_dot(ray, v);
	discriminant->c = pow(get_scalar(v), 2) - pow(sphere->diameter / 2, 2);
	discriminant->d = pow(discriminant->b, 2) - \
		4 * discriminant->a * discriminant->c;
	return (discriminant);
}

// rayとsphereとの距離
static double	calc_distance_to_object(t_discriminant *discriminant)
{
	const double	num_bottom = 2.0 * discriminant->a;
	const double	num_top1 = -1 * discriminant->b;
	const double	num_top2 = sqrt(discriminant->d);

	if (discriminant->d == 0)
		return (num_top1 / num_bottom);
	return (positive_and_min(\
				(num_top1 + num_top2) / num_bottom, \
				(num_top1 - num_top2) / num_bottom \
			));
}

// cameraからのrayとsphereとの衝突判定。衝突していれば正の距離を返す。
t_discriminant	*is_intersect_to_sphere(\
	const t_vector ray, t_camera *camera, t_sphere *sphere)
{
	t_discriminant	*discriminant;

	discriminant = calc_discriminant(ray, camera, sphere);
	if (discriminant->d >= 0)
		return (discriminant);
	free(discriminant);
	return (NULL);
}

static void	set_nearest_object(\
	t_intersection *nearest, t_sphere *sphere, double tmp_distance)
{
	nearest->sphere = sphere;
	nearest->distance = tmp_distance;
}

t_intersection	*get_nearest_object(t_vector ray, t_scene *scene)
{
	t_intersection	*nearest;
	t_discriminant	*discriminant;
	t_sphere		*sphere_cr;
	double			tmp_distance;

	nearest = (t_intersection *)malloc(sizeof(t_intersection));
	if (nearest == NULL)
		return (NULL);
	nearest->distance = INFINITY;
	sphere_cr = scene->list_sphere;
	while (sphere_cr)
	{
		discriminant = \
			is_intersect_to_sphere(ray, scene->camera, sphere_cr);
		if (discriminant)
		{
			tmp_distance = calc_distance_to_object(discriminant);
			if (tmp_distance < nearest->distance)
				set_nearest_object(nearest, sphere_cr, tmp_distance);
			free(discriminant);
		}
		sphere_cr = sphere_cr->next;
	}
	if (nearest->distance == INFINITY)
	{
		free(nearest);
		return (NULL);
	}
	return (nearest);
}
