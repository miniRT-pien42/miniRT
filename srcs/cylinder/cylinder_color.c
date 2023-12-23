#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"
#include "helpers.h"
#include "ray.h"

//シリンダーの軸が始点Aと方向ベクトルaxis(※正規化済み)で決まる
//AP 交点Pから軸始点Aへのベクトル
//Pから軸に投影する点Cは、軸の方向ベクトルaxisにそって移動する距離（APとaxisのドット積）によって決まる
//C = A + (AP・axis) * axis
static t_vector	nearest_pos_on_axis(t_vector pos, const t_cylinder *cylinder)
{
	const t_vector	ap = vec_subtract(cylinder->center, pos);
	const double height = vec_dot(cylinder->normal, ap);

	return (vec_add(cylinder->center, vec_scalar(cylinder->normal, height)));
}

//交点から中心時軸に投影したポイントPを求める
//カメラから中心軸上に投影したポイントを求め、cy半径との距離を比べる
static bool	is_inside_cylinder(t_vector pos, const t_cylinder *cylinder)
static bool	is_inside_cylinder(t_vector pos, t_cylinder *cylinder, t_vector ray)
{
	double	distances[2];
	t_ray	ray_d = (t_ray){.position = pos, .direction = ray};
	const t_vector	np = nearest_pos_on_axis(pos, cylinder);
	const double	distance_camera_to_center = get_length(vec_subtract(np, cylinder->center));

	if (distance_camera_to_center <= cylinder->diameter)
		return (true);
	calc_discriminant_for_cylinder(&ray_d, (t_cylinder *)cylinder, distances);
	if (is_intersect_cylinder(&ray_d, cylinder, fmax(distances[0], distances[1])) &&\
			!is_intersect_cylinder(&ray_d, cylinder, fmin(distances[0], distances[1])))
		return (true);
	return (false);
}

// カメラray、交点=>シリンダ中心のベクトルから内積を求める
// intersectionがcylinderのinner or outer判定して法線反転
t_vector	get_normal_on_cylinder(\
	t_scene *scene, t_intersection intersection, t_vector ray)
{
	t_vector	normal;
	t_cylinder	*cylinder;
	bool	is_intersect_inside;
	t_vector	np;//todo：cy.centerに足す

	cylinder = intersection.object;
	is_intersect_inside	= is_inside_cylinder(scene->camera->pos, cylinder, ray);
	np = nearest_pos_on_axis(intersection.position, cylinder);
	printf("is_intersect_inside: %d / intersection.position.y: %f / np.y: %f\n", is_intersect_inside, intersection.position.y, np.y);
	if (is_intersect_inside)
	{
		normal = vec_normalize(\
			vec_subtract(np, intersection.position));
	}
	else
	{
		normal = vec_normalize(\
			vec_subtract(intersection.position, np));
	}
	return (normal);
}
