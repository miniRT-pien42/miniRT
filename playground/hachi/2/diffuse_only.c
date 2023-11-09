#include <stdio.h>
#include "../utils/vector.h"

#define WIDTH 512
#define HEIGHT 512

int main()
{
	t_vec3 eye_pos  = { 0, 0, -5 };/* 視点位置 Pe */
	t_vec3 sphere_pos = { 0, 0, 5 };  /* 球の中心 Pc */
	double sphere_r = 1;                 /* 球の半径 */
	t_vec3 pw; /* スクリーン上の点pwの位置ベクトル */
	pw.z = 0;

	t_vec3 eye_dir; /* 視線方向ベクトル 𝐝e */
	t_vec3 s_c;     /* 視点 - 球の中心 𝐦⃗ 𝐩e→ から𝐜⃗ を引いたベクトル */
	double A,B,C,D;    /* 二次方程式Ax^2+Bx+C=0および判別式D */

	t_vec3 p_l = { -5, 5, -5 };  /* 光源位置 Pl */
	double t;
	t_vec3 p_i; /* 交点の位置ベクトル */
	t_vec3 v_i; /* 入射ベクトル incident vector */
	t_vec3 v_n; /* 法線ベクトル */
	double l_dot; /* 内積 */
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
			eye_dir = vec_div(&pw, &eye_pos);
			s_c = vec_div(&eye_pos, &sphere_pos);
			A = pow(get_scalar(eye_dir), 2);
			B = dot_product(&eye_dir, &s_c) * 2.0;
			C = pow(get_scalar(s_c), 2) - pow(sphere_r, 2);
			D = pow(B, 2) - 4.0 * A * C;
			if (D >= 0)
			{
				if (D == 0)
					t = -B / (2.0 * A);
				else
					t = positive_and_min(-B + sqrt(D) / (2.0 * A), -B - sqrt(D) / (2.0 * A));
				if (t > 0)
				{
					p_i = vec_sum(&eye_pos, scalar_mul(eye_dir, t));
					v_i = vec_div(&p_l, &p_i);
					v_i = v_normalize(v_i);
					v_n = vec_div(&sphere_pos, &p_i);
					v_n = v_normalize(v_n);
					l_dot = dot_product(&v_i, &v_n);
					if (l_dot < 0)
						l_dot = 0;
					c_gray = 255 * l_dot;
					printf("%d %d %d\n", c_gray, c_gray, c_gray);
				}
				else
					printf("%d %d %d\n", 0, 0, 0);//ここにはこない？
			}
			else
			{
				printf("%d %d %d\n", 200, 255, 15);
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