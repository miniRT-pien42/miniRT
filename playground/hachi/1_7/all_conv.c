#include <stdio.h>
#include "../include/vector.h"

#define WIDTH 512
#define HEIGHT 512

int main()
{
	t_vec3 eye_pos  = { 0.5, 0.5, -5 };/* 視点位置 */
	t_vec3 sphere_pos = { 0.5, 0.5, 5 };  /* 球の中心 */
	double sphere_r = 0.8;                 /* 球の半径 */
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
	int y, x;
	for(y = 0; y < HEIGHT; ++y)
	{
		pw.y = (double)y / HEIGHT;
		for(x = 0; x < WIDTH; ++x)
		{
			pw.x = (double)x / HEIGHT;
			eye_dir = vec_div(&pw, &eye_pos);
			s_c = vec_div(&eye_pos, &sphere_pos);
			A = pow(get_scalar(eye_dir), 2);
			B = dot_product(&eye_dir, &s_c) * 2.0;
			C = pow(get_scalar(s_c), 2) - pow(sphere_r, 2);
			D = pow(B, 2) - 4.0 * A * C;
			if (D >= 0)
			{
				/*printf("Yes! (D: %f) | (%d, %d) -> [%f, %f, %f]\n", D, x, y, pw.x, pw.y, pw.z);*/
				printf("%d %d %d\n", 0, 0, 0);
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
$ gcc -std=c89 -Wall all_conv.c ../utils/vector.c -lm -o all_conv
$ ./all_conv > all_conv.ppm
$ display all_conv.ppm
*/