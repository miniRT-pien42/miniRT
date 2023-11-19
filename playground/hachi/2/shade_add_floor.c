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
	t_primitive		*sphere;
	t_primitive		*plane;
	t_light_ambient	*light_ambient;
	t_light			*light;

	scene = (t_scene *)malloc(sizeof (t_scene));
	plane = (t_primitive *)malloc(sizeof (t_primitive));
	sphere = (t_primitive *)malloc(sizeof (t_primitive));
	light_ambient = (t_light_ambient *)malloc(sizeof (t_light_ambient));
	light = (t_light *)malloc(sizeof (t_light));
	if (scene == NULL || sphere == NULL || light_ambient == NULL || light == NULL || plane == NULL)
		return (1);

	sphere->type = SPHERE;
	sphere->center = init_vec3(0, 0, 0);
	sphere->diameter = 0.8;
	sphere->color = init_color(255, 10, 10);
	sphere->next = NULL;

	plane->type = PLANE;
	plane->center = init_vec3(0, -0.7, 0);
	plane->v_n_norm = init_vec3(0, 1, 0);
	plane->color = init_color(88, 106, 229);
	plane->next = sphere;

	light_ambient->e_a = 0.1;
	light_ambient->color = init_color(122, 255, 122);

	light->pos = init_vec3(-5, 5, -5);
	light->e_i = 0.5;

	scene->light_ambient = light_ambient;
	scene->lights = light;
	scene->eye_pos  = init_vec3( 0, 0, -5 );
	scene->list_primitive = plane;

	t_vec3 pw; /* スクリーン上の点pwの位置ベクトル */
	pw.z = 0;

	t_vec_dir	*ray;//視線方向ベクトル 𝐝e これがray!
	t_vec3	vec_ray;
	ray = (t_vec_dir *)malloc(sizeof (t_vec_dir));
	if (ray == NULL)
		return (1);
	ray->start = scene->eye_pos;
	//ray->directionは座標ごと違うのでloopの中で

	t_rgb color_final;
	t_point	*nearest;
	nearest = (t_point *)malloc(sizeof (t_point));
	if (nearest == NULL)
		return (1);

	printf("P3\n"); /* マジックナンバー */
	printf("%d %d\n", WIDTH, HEIGHT); /* 幅と高さ */
	printf("255\n"); /* 色深度 */
	int y, x;
	for(y = 0; y < HEIGHT; ++y)
	{
		pw.y = -2.0 * y / (HEIGHT - 1) + 1.0;
		for(x = 0; x < WIDTH; ++x)
		{
			//printf("x: %d y: %d\n", x, y);
			pw.x = 2.0 * x / (WIDTH - 1) - 1.0;
			ray->direction = pw;
			//printf("for 1\n");
			vec_ray = get_vec_ray(ray);
			//printf("for 2\n");
			nearest = get_nearest_primitive(scene, &vec_ray, 1000.0, 0);
			//printf("for 3 null %d\n", nearest==NULL);
			color_final = raytrace(scene, &vec_ray, nearest);
			//printf("for 4\n");
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