#include <stdio.h>
#include "../include/vector.h"

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
	double Ka = 0.5; /* 環境光反射係数 */
	double Ea = 0.8; /* 環境光の照度 */
	double La = Ka * Ea; /* 環境光の輝度 */
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
			eye_dir = vec_div(&eye_pos, &pw);
			//printf("eye_dir x:%f y:%f z:%f\n", eye_dir.x, eye_dir.y, eye_dir.z);
			s_c = vec_div(&sphere_pos, &eye_pos);
			A = pow(get_scalar(eye_dir), 2);
			B = dot_product(&eye_dir, &s_c) * 2.0;
			C = pow(get_scalar(s_c), 2) - pow(sphere_r, 2);
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
					p_i = vec_sum(&eye_pos, scalar_mul(eye_dir, t));//p_i 交点の位置
					v_i = vec_div(&p_i, &p_l);// 入射ベクトル 接点から光源へ
					v_i = v_normalize(v_i);
					v_n = vec_div(&sphere_pos, &p_i);// 球面の法線 球centerから接点へ
					v_n = v_normalize(v_n);
					l_dot = dot_product(&v_i, &v_n);// 入射と法線の内積 1に近いほど平行に近い
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
$ gcc -std=c99 -Wall simple_shading.c ../utils/vector.c -lm -o simple_shading
$ ./simple_shading > result.ppm
$ display result.ppm
*/