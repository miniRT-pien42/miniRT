
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"

t_vec3	init_vec3(double x, double y, double z)
{
	t_vec3	v_return;

	v_return.x = x;
	v_return.y = y;
	v_return.z = z;
	return (v_return);
}

t_vec3	vec_sum(const t_vec3 *v1, const t_vec3 *v2)
{
	t_vec3	v_return;

	v_return.x = v1->x + v2->x;
	v_return.y = v1->y + v2->y;
	v_return.z = v1->z + v2->z;
	return (v_return);
}

t_vec3	vec_div(const t_vec3 *v1, const t_vec3 *v2)
{
	t_vec3	v_return;

	v_return.x = v2->x - v1->x;
	v_return.y = v2->y - v1->y;
	v_return.z = v2->z - v1->z;
	return (v_return);
}

t_vec3	*scalar_mul(t_vec3 v, double scalar)
{
	t_vec3	*v_return;

	v_return = (t_vec3 *)malloc(sizeof(t_vec3));
	if (v_return == NULL)
		return (NULL);
	v_return->x = v.x * scalar;
	v_return->y = v.y * scalar;
	v_return->z = v.z * scalar;
	return (v_return);
}

double	dot_product(const t_vec3 *v1, const t_vec3 *v2)/* 内積 */
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec3	cross_product(const t_vec3 *v1, const t_vec3 *v2)
{
	t_vec3	v_return;

	v_return.x = v1->y * v2->z - v1->z * v2->y;
	v_return.y = v1->z * v2->x - v1->x * v2->z;
	v_return.z = v1->x * v2->y - v1->y * v2->x;
	return (v_return);
}

double	get_scalar(const t_vec3 v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vec3	v_normalize(const t_vec3 v)
{
	t_vec3	v_return;
	double	scalar_v;

	scalar_v = get_scalar(v);
	v_return.x = v.x / scalar_v;
	v_return.y = v.y / scalar_v;
	v_return.z = v.z / scalar_v;
	return (v_return);
}

double	convert_deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}

double	convert_rad_to_deg(double rad)
{
	return (rad * 180.0 / M_PI);
}

t_vec3	*convert_pw_coordinate(t_vec3 *v_co, int w, int h)
{
	v_co->x /= w;
	v_co->y /= h;
	return (v_co);
}

double	positive_and_min(double a, double b)
{
	if (a * b < 0)
		return (a < b ? b : a);
	return (a < b ? a : b);
}
