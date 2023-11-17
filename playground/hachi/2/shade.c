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
	//sphere->color = init_color(100, 100, 100);//ここがグレーだとshadeがつかない
	sphere->color = init_color(255, 10, 10);//ここがグレーでなければshadeがつく
	sphere->next = NULL;

	light_ambient->e_a = 0.8;
	light_ambient->color = init_color(100, 255, 100);

	light->pos = init_vec3(-5, 5, -5);
	light->e_i = 0.8;

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

	t_rgb color_final;

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
			color_final = raytrace(scene, &vec_ray, &vec_sphere_to_eye);
			printf("%d %d %d ", color_final.r, color_final.g, color_final.b);
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