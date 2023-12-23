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
{
	const t_vector	np = nearest_pos_on_axis(pos, cylinder);
	const double	distance_camera_to_center = get_length(vec_subtract(np, cylinder->center));

	if (distance_camera_to_center <= cylinder->diameter)
		return (true);
	return (false);
}

//カメラray、交点=>シリンダ中心のベクトルから内積を求めて、内外判定で法線反転
t_vector	get_normal_on_cylinder(\
	t_scene *scene, t_intersection intersection, t_vector ray)
{
	(void)ray;
	t_vector			normal;
	const t_cylinder	*cylinder = intersection.object;
	const bool	is_camera_inside	= is_inside_cylinder(scene->camera->pos, cylinder);
	const t_vector	np = nearest_pos_on_axis(intersection.position, cylinder);

	if (is_camera_inside)
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
