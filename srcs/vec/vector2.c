#include <math.h>
#include "vector.h"

t_vector	vec_scalar(const t_vector v, double scalar)
{
	t_vector	ret_v;

	if (v.x == 0 && scalar == INFINITY)
		ret_v.x = 0;
	else
		ret_v.x = v.x * scalar;
	if (v.y == 0 && scalar == INFINITY)
		ret_v.y = 0;
	else
		ret_v.y = v.y * scalar;
	if (v.z == 0 && scalar == INFINITY)
		ret_v.z = 0;
	else
		ret_v.z = v.z * scalar;
	return (ret_v);
}

t_vector	vec_normalize(const t_vector v)
{
	const double	length = vec_norm(v);
	const t_vector	ret_v = {v.x / length, v.y / length, v.x / length};

	return (ret_v);
}

double	get_scalar(const t_vector v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

double	get_angle(const t_vector v1, const t_vector v2)
{
	return (acos(vec_dot(v1, v2)));
}
