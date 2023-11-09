#include <stdio.h>
#include "../utils/vector.h"

#define WIDTH 512
#define HEIGHT 512

int main()
{
	t_vec3 eye_pos  = { 0.5, 0.5, -5 };/* 視点位置 */
	t_vec3 sphere_pos = { 0, 0, 5 };  /* 球の中心 */
	double sphere_r = 1;                 /* 球の半径 */
	t_vec3 pw = { 382, 255, 0 };/* スクリーン上の点 382,255 */
	convert_pw_coordinate(&pw, WIDTH, HEIGHT);

	t_vec3 eye_dir; /* 視線方向ベクトル */
	t_vec3 s_c;     /* 視点 - 球の中心 */
	double A,B,C,D;    /* 二次方程式Ax^2+Bx+C=0および判別式D */

	/*printf("%f / %f / %f\n", pw.x, pw.y, pw.z);*/
	eye_dir = vec_div(&pw, &eye_pos);
	s_c = vec_div(&eye_pos, &sphere_pos);

	A = pow(get_scalar(eye_dir), 2);
	B = dot_product(&eye_dir, &s_c) * 2.0;
	C = pow(get_scalar(s_c), 2) - pow(sphere_r, 2);
	D = pow(B, 2) - 4.0 * A * C;
	if (D >= 0)
		printf("Yes! (D: %f)\n", D);
	else
		printf("No... (D: %f)\n", D);
	return (0);
}