#include <stdio.h>
#include <stdlib.h>
#include "../include/vector.h"
#include "../include/scene.h"
#include "../include/ray.h"
#include "../include/light.h"
#include "../include/primitive.h"

#define WIDTH 512
#define HEIGHT 512

int main()
{
	t_scene			*scene;
	t_sphere		*sphere;
	t_light_ambient	*light_ambient;
	t_light			*light;

	scene = (t_scene *)malloc(sizeof (t_scene));
	sphere = (t_sphere *)malloc(sizeof (t_sphere));
	light_ambient = (t_light_ambient *)malloc(sizeof (t_light_ambient));
	light = (t_light *)malloc(sizeof (t_light));
	if (scene == NULL || sphere == NULL || light_ambient == NULL || light == NULL)
		return (1);

	sphere->center = init_vec3(0, 0, 5);
	sphere->diameter = 1;
	sphere->color = init_color(255, 255, 255);
	sphere->k_a = 0.5;
	sphere->next = NULL;

	light_ambient->e_a = 0.8;
	light_ambient->color = init_color(255, 255, 255);

	light->pos = init_vec3(-5, 5, -5);
	light->e_a = 0.8;

	scene->light_ambient = light_ambient;
	scene->lights = light;
	scene->list_plane = NULL;
	scene->list_sphere = sphere;
	scene->list_cylinder = NULL;
	scene->eye_pos  = init_vec3( 0, 0, -5 );

	t_vec3 pw; /* スクリーン上の点pwの位置ベクトル */
	pw.z = 0;

	t_vec_dir	*ray;//視線方向ベクトル 𝐝e これがray!　eye_dirから置き換え
	t_vec3	vec_ray;
	ray = (t_vec_dir *)malloc(sizeof (t_vec_dir));
	if (ray == NULL)
		return (1);
	ray->start = scene->eye_pos;
	//ray->directionは座標ごと違うのでloopの中で

	t_vec_dir	*sphere_to_eye;
	t_vec3	vec_sphere_to_eye;
	sphere_to_eye = (t_vec_dir *)malloc(sizeof (t_vec_dir));
	if (sphere_to_eye == NULL)
		return (1);
	sphere_to_eye->start = sphere->center;
	sphere_to_eye->direction = scene->eye_pos;

	t_point	*intersection_point;
	double l_dot; /* 内積 */
	double La = sphere->k_a * light_ambient->e_a; /* 環境光の輝度 */
	double Lr; /* 物体表面の輝度 */
	int c_gray;

	printf("P3\n"); /* マジックナンバー */
	printf("%d %d\n", WIDTH, HEIGHT); /* 幅と高さ */
	printf("255\n"); /* 色深度 */
	int y, x;
	for(y = 0; y < HEIGHT; ++y)
	{
		pw.y = -2.0 * y / (HEIGHT - 1) + 1.0;
		for(x = 0; x < WIDTH; ++x)
		{
			pw.x = 2.0 * x / (WIDTH - 1) - 1.0;
			ray->direction = pw;
			vec_ray = get_vec_ray(ray);
			//printf("vec_ray x:%f y:%f z:%f\n", vec_ray.x, vec_ray.y, vec_ray.z);
			vec_sphere_to_eye = get_vec_ray(sphere_to_eye);
			intersection_point = intersection_ray_sphere(sphere, vec_ray, vec_sphere_to_eye);
			if (intersection_point == NULL)
			{
				printf("%d %d %d\n", 200, 0, 237);
				continue ;
			}
			if (intersection_point->distance > 0)
			{
				intersection_point->position = vec_sum(&scene->eye_pos, scalar_mul(vec_ray, intersection_point->distance));
				intersection_point->incident = get_vec_ray_sd_norm(intersection_point->position, light->pos);// 入射ベクトル 接点から光源へ
				intersection_point->normal = get_vec_ray_sd_norm(sphere->center, intersection_point->position);
				l_dot = dot_product(&intersection_point->incident, &intersection_point->normal);// 入射と法線の内積 1に近いほど平行に近い
				//printf("l_dot:%f (%d, %d)\n", l_dot, x, y);
				if (l_dot < 0)
					l_dot = 0;
				Lr = La + l_dot;
				if (Lr < 0)
					Lr = 0;
				else if (Lr > 1)
					Lr = 1;
				c_gray = 255 * Lr;
				printf("%d %d %d\n", c_gray, c_gray, c_gray);
			}
			else
				printf("%d %d %d\n", 0, 0, 0);
		}
		printf("\n");
	}
	return (0);
}

/*
$ gcc -std=c99 -Wall diffuse_only.c ../utils/vector.c -lm -o diffuse_only
$ ./diffuse_only > result.ppm
$ display result.ppm
*/