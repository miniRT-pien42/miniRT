#include <stdio.h>
#include <stdlib.h>
#include "../include/vector.h"
#include "../include/primitive.h"

#define WIDTH 256
#define HEIGHT 256
#define EPSILON (1.0f/512)

int main()
{
	t_vec3 eye_pos  = { 0, 0, -5 };/* 視点位置 */
	t_sphere sphere[5];
	double list_pos_z[5];
	ssize_t closest;
	sphere[0].center = init_vec3(0, 0, -7);
	sphere[1].center = init_vec3(0, 0, 5);
	sphere[2].center = init_vec3(0.5, 0, 3);
	sphere[3].center = init_vec3(0.5, 1, -2);
	sphere[4].center = init_vec3(-1, -1, 10);
	sphere[0].diameter = 1;
	sphere[1].diameter = 0.8;
	sphere[2].diameter = 0.2;
	sphere[3].diameter = 0.1;
	sphere[4].diameter = 1;
	sphere[0].color = init_color(255, 0, 0);
	sphere[1].color = init_color(0, 255, 0);
	sphere[2].color = init_color(0, 0, 255);
	sphere[3].color = init_color(0, 0, 0);
	sphere[4].color = init_color(100, 10, 100);
	t_vec3 pw;
	pw.z = 0;

	/*t_vec3 pw = { 382, 255, 0 };
	convert_pw_coordinate(&pw, WIDTH, HEIGHT);*/

	t_vec3 eye_dir; /* 視線方向ベクトル */
	t_vec3 s_c;     /* 視点 - 球の中心 */
	double A,B,C,D;    /* 二次方程式Ax^2+Bx+C=0および判別式D */

	t_vec3 p_l = { -5, 5, -5 };  /* 光源位置 Pl */
	t_vec3 p_i; /* 交点の位置ベクトル */
	t_vec3 v_i; /* 入射ベクトル incident vector */
	t_vec3 v_n; /* 法線ベクトル */
	double l_dot; /* 内積 */

	/*printf("%f / %f / %f\n", pw.x, pw.y, pw.z);*/
	printf("P3\n"); /* マジックナンバー */
	printf("%d %d\n", WIDTH, HEIGHT); /* 幅と高さ */
	printf("255\n"); /* 色深度 */
	int y, x, i = 0;
	for(y = 0; y < HEIGHT; ++y)
	{
		pw.y = -2.0 * y / (HEIGHT - 1) + 1.0;
		for(x = 0; x < WIDTH; ++x)
		{
			pw.x = 2.0 * x / (WIDTH - 1) - 1.0;
			eye_dir = vec_div(&pw, &eye_pos);
			while (i < 5)
			{
				s_c = vec_div(&eye_pos, &sphere[i].center);
				A = pow(get_scalar(eye_dir), 2);
				B = dot_product(&eye_dir, &s_c) * 2.0;
				C = pow(get_scalar(s_c), 2) - pow(sphere[i].diameter, 2);
				D = pow(B, 2) - 4.0 * A * C;
				if (D > 0)
				{
					//printf("ttt: %d:: %f %f \n", i, (-B + sqrt(D)) / (2.0 * A), (-B - sqrt(D)) / (2.0 * A));
					list_pos_z[i] = positive_and_min((-B + sqrt(D)) / (2.0 * A), (-B - sqrt(D)) / (2.0 * A));
					//printf("list_pos_z[i]: %d:: %f \n", i, list_pos_z[i]);
				}
				else
					list_pos_z[i] = -1.0;
				i++;
			}
			i = 0;
			closest = extract_closest(list_pos_z, 5);
			//printf("closest: %zi:: %f \n", closest, list_pos_z[closest]);
			if (closest >= 0)
			{
				p_i = vec_sum(&eye_pos, scalar_mul(eye_dir, list_pos_z[closest]));//p_i 交点の位置
				v_i = vec_div(&p_i, &p_l);
				v_i = v_normalize(v_i);
				while (i < 5)
				{
					if (i == closest)
						continue ;
					v_n = vec_div(&sphere[i].center, &p_i);// 球面の法線 球centerから接点へ
					v_n = v_normalize(v_n);
					i++;
				}
				//todo: v_iが他のオブジェクトと交点を持てば影が落ちる
				printf("%d %d %d\n", sphere[closest].color.r, sphere[closest].color.g, sphere[closest].color.b);
			}
			else
			{
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