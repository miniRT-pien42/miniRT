
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

t_point	*intersection_ray_plane(const t_plane *plane, const t_vec3 vec_ray, const t_vec3 vec_plane_to_eye)
{
	double t, denominator;
	t_point	*return_intersection;

	denominator = dot_product(&vec_ray, &plane->v_n_norm);
	if (denominator == 0)
		return (NULL);
	t = dot_product(&vec_plane_to_eye, &plane->v_n_norm) / denominator * -1;
	if (t < 0)
		return (NULL);
	return_intersection = (t_point *)malloc(sizeof(t_point));
	if (return_intersection == NULL)
		return (NULL);
	if (t == 0)
		return_intersection->distance = 0;
	else
		return_intersection->distance = t;
	return (return_intersection);
}

static t_f_rgb	get_l_a(const t_scene *scene)
{
	t_f_rgb	l_a;

	l_a.f_r = scene->light_ambient->color.r / 255.0 * scene->light_ambient->e_a;
	l_a.f_g = scene->light_ambient->color.g / 255.0 * scene->light_ambient->e_a;
	l_a.f_b = scene->light_ambient->color.b / 255.0 * scene->light_ambient->e_a;
	return (l_a);
}

static t_f_rgb	get_l_d(const t_scene *scene, double l_dot)
{
	t_f_rgb	l_d;

	l_d.f_r = scene->list_sphere->color.r / 255.0 * scene->lights->e_i * l_dot;
	l_d.f_g = scene->list_sphere->color.g / 255.0 * scene->lights->e_i * l_dot;
	l_d.f_b = scene->list_sphere->color.b / 255.0 * scene->lights->e_i * l_dot;
	return (l_d);
}

static t_f_rgb	get_l_r(t_f_rgb l_a, t_f_rgb l_d)
{
	t_f_rgb l_r;

	l_r.f_r = clamp_f(l_a.f_r + l_d.f_r, 0, 1);
	l_r.f_g = clamp_f(l_a.f_g + l_d.f_g, 0, 1);
	l_r.f_b = clamp_f(l_a.f_b + l_d.f_b, 0, 1);
	return (l_r);
}

//シーンにおける，単一のレイでの光線追跡を行い，その点での色を返す．
t_rgb raytrace(
		const t_scene *scene,   /* 【入力】交差判定対象のシーン */
		const t_vec3 *vec_ray,   /* 視線方向ベクトル 𝐝e これがray! */
		const t_vec3 *vec_sphere_to_eye,
		const t_vec3 *vec_plane_to_eye
)
{
	t_point	*isp_sphere;
	t_point	*isp_plane;
	t_rgb	out_col;
	isp_sphere = intersection_ray_sphere(scene->list_sphere, *vec_ray, *vec_sphere_to_eye);
	isp_plane = intersection_ray_plane(scene->list_plane, *vec_ray, *vec_plane_to_eye);
	if (isp_sphere == NULL && isp_plane == NULL) //背景色のままreturn
	{
		out_col = init_color(200, 0, 237);
	}
//	else if (isp_sphere->distance == 0 || isp_plane->distance == 0)
//	{
//		printf("raytrace 2\n");
//		out_col = init_color(0, 0, 0);
//	}
	else
	{
		if (isp_sphere == NULL)
			out_col = init_color(100, 100, 237);
		else
		{
			double l_dot; /* 内積 */
			isp_sphere->position = vec_sum(&scene->eye_pos, scalar_mul(*vec_ray, isp_sphere->distance));
			isp_sphere->incident = get_vec_ray_sd_norm(isp_sphere->position, scene->lights->pos);// 入射ベクトル 接点から光源へ
			isp_sphere->normal = get_vec_ray_sd_norm(scene->list_sphere->center, isp_sphere->position);
			l_dot = dot_product(&isp_sphere->incident, &isp_sphere->normal);// 入射と法線の内積 1に近いほど平行に近い
			l_dot = clamp_f(l_dot, 0, 1);

			t_f_rgb l_a; /* 環境光の輝度 */
			t_f_rgb l_d; /* 直接光の拡散反射光の輝度 */
			t_f_rgb l_r; /* 物体表面の輝度 */

			l_a = get_l_a(scene);
			l_d = get_l_d(scene, l_dot);
			l_r = get_l_r(l_a, l_d);
			out_col = init_color(l_r.f_r * 255, l_r.f_g * 255, l_r.f_b * 255);
		}
	}
	return (out_col);
}
