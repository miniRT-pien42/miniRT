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

	light->pos = init_vec3(-5, 5, -55);
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
	ray = (t_vec_dir *)malloc(sizeof (t_vec_dir));
	if (ray == NULL)
		return (1);
	ray->start = scene->eye_pos;
	t_vec3	vec_ray;
	t_vec_dir	*to_sphere_center;     /* 球の中心への視点 - 球の中心 𝐦⃗ 𝐩e→ から𝐜⃗ を引いたベクトル */
	to_sphere_center = (t_vec_dir *)malloc(sizeof (t_vec_dir));
	if (to_sphere_center == NULL)
		return (1);
	to_sphere_center->start = sphere->center;
	to_sphere_center->direction = scene->eye_pos;
	t_vec3	vec_to_sphere_center;
	double A,B,C,D;    /* 二次方程式Ax^2+Bx+C=0および判別式D */

	double t;
	t_vec3 p_i; /* 交点の位置ベクトル */
	t_vec3 v_i; /* 入射ベクトル incident vector */
	t_vec3 v_n; /* 法線ベクトル */
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
			vec_to_sphere_center = get_vec_ray(to_sphere_center);
			A = pow(get_scalar(vec_ray), 2);
			B = dot_product(&vec_ray, &vec_to_sphere_center) * 2.0;
			C = pow(get_scalar(vec_to_sphere_center), 2) - pow(sphere->diameter, 2);
			D = pow(B, 2) - 4.0 * A * C;
			if (D >= 0)
			{
				if (D == 0)
					t = -B / (2.0 * A);
				else
					t = positive_and_min((-B + sqrt(D)) / (2.0 * A), (-B - sqrt(D)) / (2.0 * A));
				//printf("A:%f B:%f C:%f D:%f t:%f\n", A, B, C, D, t);
				if (t > 0)
				{
					p_i = vec_sum(&scene->eye_pos, scalar_mul(vec_ray, t));//p_i 交点の位置
					v_i = vec_div(&p_i, &light->pos);// 入射ベクトル 接点から光源へ
					v_i = v_normalize(v_i);
					v_n = vec_div(&sphere->center, &p_i);// 球面の法線 球centerから接点へ
					v_n = v_normalize(v_n);
					l_dot = dot_product(&v_i, &v_n);// 入射と法線の内積 1に近いほど平行に近い
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
			else
			{
				printf("%d %d %d\n", 200, 0, 237);
			}
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