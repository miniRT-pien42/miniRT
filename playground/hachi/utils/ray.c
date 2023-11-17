
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

t_vec3	get_vec_ray_norm(const t_vec_dir *ray)
{
	t_vec3	vec_ray;

	vec_ray = get_vec_ray(ray);
	return (v_normalize(vec_ray));
}

t_vec3	get_vec_ray_sd(const t_vec3 start, const t_vec3 direction)
{
	t_vec3	vec_ray;

	vec_ray.x = direction.x - start.x;
	vec_ray.y = direction.y - start.y;
	vec_ray.z = direction.z - start.z;
	return (vec_ray);
}

t_vec3	get_vec_ray_sd_norm(const t_vec3 start, const t_vec3 direction)
{
	t_vec3	vec_ray;

	vec_ray = get_vec_ray_sd(start, direction);
	return (v_normalize(vec_ray));
}

//レイと単一の物体との交差判定を行う．
// 交点が存在する場合は，その点への距離と位置と，その位置での法線ベクトルを返す．
// 交点が存在しない場合は，NULLを返す．
t_point	*intersection_ray_sphere( const t_sphere *sphere, const t_vec3 vec_ray, const t_vec3 vec_sphere_to_eye)
{
	double A,B,C,D;    /* 二次方程式Ax^2+Bx+C=0および判別式D */
	t_point	*return_intersection;

	A = pow(get_scalar(vec_ray), 2);
	B = dot_product(&vec_ray, &vec_sphere_to_eye) * 2.0;
	C = pow(get_scalar(vec_sphere_to_eye), 2) - pow(sphere->diameter, 2);
	D = pow(B, 2) - 4.0 * A * C;
	if (D < 0)
		return (NULL);
	return_intersection = (t_point *)malloc(sizeof(t_point));
	if (return_intersection == NULL)
		return (NULL);
	if (D == 0)
		return_intersection->distance = -B / (2.0 * A);
	else
		return_intersection->distance = positive_and_min((-B + sqrt(D)) / (2.0 * A), (-B - sqrt(D)) / (2.0 * A));
	return (return_intersection);
}

//シーンにおける，単一のレイでの光線追跡を行い，その点での色を返す．
t_rgb raytrace(
		const t_scene *scene,   /* 【入力】交差判定対象のシーン */
		const t_vec3 *vec_ray,   /* 視線方向ベクトル 𝐝e これがray! */
		const t_vec3 *vec_sphere_to_eye
)
{
	t_point	*intersection_point;
	double l_dot; /* 内積 */
	double La = scene->list_sphere->k_a * scene->light_ambient->e_a; /* 環境光の輝度 */
	double Lr; /* 物体表面の輝度 */
	int c_gray;
	t_rgb	out_col;

	intersection_point = intersection_ray_sphere(scene->list_sphere, *vec_ray, *vec_sphere_to_eye);
	if (intersection_point == NULL) //背景色のままreturn
		out_col = init_color(200, 0, 237);
	else if (intersection_point->distance == 0)
		out_col = init_color(0, 0, 0);
	else
	{
		intersection_point->position = vec_sum(&scene->eye_pos, scalar_mul(*vec_ray, intersection_point->distance));
		intersection_point->incident = get_vec_ray_sd_norm(intersection_point->position, scene->lights->pos);// 入射ベクトル 接点から光源へ
		intersection_point->normal = get_vec_ray_sd_norm(scene->list_sphere->center, intersection_point->position);
		l_dot = dot_product(&intersection_point->incident, &intersection_point->normal);// 入射と法線の内積 1に近いほど平行に近い
		l_dot = clamp_f(l_dot, 0, 1);
		Lr = La + l_dot;
		Lr = clamp_f(Lr, 0, 1);
		c_gray = 255 * Lr;
		out_col = init_color(c_gray, c_gray, c_gray);
	}
	return (out_col);
}
