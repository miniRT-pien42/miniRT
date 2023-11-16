
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/ray.h"
#include "../include/scene.h"

t_rgb	init_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_rgb	color_return;

	color_return.r = r;
	color_return.g = g;
	color_return.b = b;
	return (color_return);
}

t_vec3	get_vec_ray(const t_vec_dir *ray)
{
	t_vec3	vec_ray;

	vec_ray.x = ray->direction.x - ray->start.x;
	vec_ray.y = ray->direction.y - ray->start.y;
	vec_ray.z = ray->direction.z - ray->start.z;
	return (vec_ray);
}

//レイと単一の物体との交差判定を行う．
// 交点が存在する場合は，その点への距離と位置と，その位置での法線ベクトルを返す．
// 交点が存在しない場合は，NULLを返す．
//t_point_intersection *intersection_test_sphere( const t_sphere *sphere, const t_vec_dir	*ray)
//{
//	t_point_intersection	*out_intp;
//	double A,B,C,D;    /* 二次方程式Ax^2+Bx+C=0および判別式D */
//
//	out_intp = (t_point_intersection *)malloc(sizeof(t_point_intersection));
//	if (out_intp == NULL)
//		return (NULL);
//	A = pow(get_scalar(get_vec_ray(ray)), 2);
//	B = dot_product(get_vec_ray(ray), &s_c) * 2.0;
//	C = pow(get_scalar(s_c), 2) - pow(sphere->diameter, 2);
//	D = pow(B, 2) - 4.0 * A * C;
//
//
//	return (out_intp);
//}

//シーンにおける，単一のレイでの光線追跡を行い，その点での色を返す．
int raytrace(
		const t_scene *scene,   /* 【入力】交差判定対象のシーン */
		const t_vec_dir *eye_ray   /* 【入力】交差判定の対象のレイ */
)
{
	(void)scene;
	t_rgb	*out_col;

	(void)out_col;
	(void)eye_ray;
	out_col = (t_rgb *)malloc(sizeof(t_rgb));
	return (0);
}
