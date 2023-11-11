#include <stdio.h>
#include <stdlib.h>
#include "../include/vector.h"
#include "../include/sphere.h"

#define WIDTH 512
#define HEIGHT 512

int main()
{
	t_vec3 eye_pos  = { 0.5, 0.5, -5 };/* 視点位置 */
	t_sphere sphere[5];
	size_t list_pos_z[5];
	size_t closest;
	sphere[0].center = init_vec3(-0.1, 0, 5);
	sphere[1].center = init_vec3(0.1, -0.1, 5);
	sphere[2].center = init_vec3(0.3, 0.5, 0);
	sphere[3].center = init_vec3(0.5, 1, -2);
	sphere[4].center = init_vec3(0.8, 0.5, 10);
	sphere[0].diameter = 1;
	sphere[1].diameter = 0.5;
	sphere[2].diameter = 0.8;
	sphere[3].diameter = 0.2;
	sphere[4].diameter = 1;
	sphere[0].color = init_color(255, 0, 0);
	sphere[1].color = init_color(0, 255, 0);
	sphere[2].color = init_color(0, 0, 255);
	sphere[3].color = init_color(255, 255, 0);
	sphere[4].color = init_color(255, 0, 255);
	t_vec3 pw;
	pw.z = 0;

	/*t_vec3 pw = { 382, 255, 0 };
	convert_pw_coordinate(&pw, WIDTH, HEIGHT);*/

	t_vec3 eye_dir; /* 視線方向ベクトル */
	t_vec3 s_c;     /* 視点 - 球の中心 */
	double A,B,C,D;    /* 二次方程式Ax^2+Bx+C=0および判別式D */

	/*printf("%f / %f / %f\n", pw.x, pw.y, pw.z);*/
	printf("P3\n"); /* マジックナンバー */
	printf("%d %d\n", WIDTH, HEIGHT); /* 幅と高さ */
	printf("255\n"); /* 色深度 */
	int y, x, i = 0;
	for(y = 0; y < HEIGHT; ++y)
	{
		pw.y = (double)y / HEIGHT;
		for(x = 0; x < WIDTH; ++x)
		{
			pw.x = (double)x / HEIGHT;
			eye_dir = vec_div(&pw, &eye_pos);
			while (i < 5)
			{
				s_c = vec_div(&eye_pos, &sphere[i].center);
				A = pow(get_scalar(eye_dir), 2);
				B = dot_product(&eye_dir, &s_c) * 2.0;
				C = pow(get_scalar(s_c), 2) - pow(sphere[i].diameter, 2);
				D = pow(B, 2) - 4.0 * A * C;
				list_pos_z[i] = D;
				i++;
			}
			closest = extract_closest(list_pos_z, 5);
			if (closest >= 0)
			{
				/*printf("Yes! (D: %f) | (%d, %d) -> [%f, %f, %f]\n", D, x, y, pw.x, pw.y, pw.z);*/
				printf("%d %d %d\n", sphere[closest].color.r, sphere[closest].color.g, sphere[closest].color.b);
			}
			else
			{
				/*printf("No... (D: %f) | (%d, %d) -> [%f, %f, %f]\n", D, x, y, pw.x, pw.y, pw.z);*/
				printf("%d %d %d\n", 255, 255, 255);
			}
		}/* for */
		printf("\n");
	}/* for */
	return (0);
}

/*
$ gcc -std=c99 -Wall multi_obj.c ../utils/vector.c ../utils/ray.c ../object/sphere.c -lm -o multi_obj
$ ./multi_obj > multi_obj.ppm
$ display multi_obj.ppm
*/