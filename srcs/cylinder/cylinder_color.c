#include "display.h"
#include "error.h"
#include "helpers.h"
#include "ray.h"
#include "scene.h"
#include "vector.h"
#include <stdlib.h>
#include <math.h>

//intersectionではない方の交点は、
// 1より大きければ向こう側。
// 1より小さくて正なら手前側（影の元）
// 負ならライトは中にある
bool	is_cylinder_self_shadow(\
	t_intersection intersection, const t_ray *ray_shadow)
{
	double		distances[2];
	double		discriminant;

	discriminant = \
		calc_discriminant_for_cylinder(ray_shadow, intersection.object, distances);
	if (discriminant <= 0)
		return (false);
	if (distances[0] < (1.0 - EPSILON) && distances[0] > EPSILON && \
		is_intersect_cylinder(ray_shadow, intersection.object, distances[0]))
		return (true);
	return (false);
}

//シリンダーの軸が始点Aと方向ベクトルaxis(※正規化済み)で決まる
//AP 交点Pから軸始点Aへのベクトル
//Pから軸に投影する点Cは、軸の方向ベクトルaxisにそって移動する距離（APとaxisのドット積）によって決まる
//C = A + (AP・axis) * axis
static t_vector	nearest_pos_on_axis(t_vector pos, const t_cylinder *cylinder)
{
	const t_vector	ap = vec_subtract(cylinder->center, pos);
	const double	height = vec_dot(cylinder->normal, ap);

	return (vec_add(cylinder->center, vec_scalar(cylinder->normal, -height)));
}

//交点から中心時軸に投影したポイントPを求める
//カメラから中心軸上に投影したポイントを求め、cy半径との距離を比べる
bool	is_camera_inside_cylinder(const t_cylinder *cylinder, const t_ray *ray_shadow)
{
	double		distances[2];
	double		discriminant;

	discriminant = calc_discriminant_for_cylinder(\
		ray_shadow, (t_cylinder *)cylinder, distances);
	if (discriminant < 0)
		error_exit(ERR_INTERSECTION);
	//片方が負ならシリンダ内部にカメラがある
	if ((distances[0] > 0 && distances[1] < 0) || \
		(distances[0] < 0 && distances[1] > 0) || \
		(fabs(distances[0]) < EPSILON && distances[1] > 0) || \
		(fabs(distances[1]) < EPSILON && distances[0] > 0))
		return (true);
	//共に正ならシリンダを外から見ている。見えているポイントが指定された高さの範囲内なら外側が見えている
	if (is_intersect_cylinder(\
		ray_shadow, cylinder, fmin(distances[0], distances[1])))
		return (false);
	//共に正でシリンダを外から見ているが、外側は指定の高さ範囲外。内側なら範囲内。
	if (is_intersect_cylinder(\
		ray_shadow, cylinder, fmax(distances[0], distances[1])))
		return (true);
	return (false);
}

// カメラray、交点=>シリンダ中心のベクトルから内積を求める
// intersectionがcylinderのinner or outer判定して法線反転
t_vector	get_normal_on_cylinder(t_intersection intersection, const t_ray *ray)
{
	t_vector			normal;
	const t_cylinder	*cylinder = intersection.object;
	const bool			is_inside_view = is_camera_inside_cylinder(cylinder, ray);
	const t_vector		np = \
		nearest_pos_on_axis(intersection.position, cylinder);

	if (is_inside_view)
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
