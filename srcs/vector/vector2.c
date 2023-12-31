#include "vector.h"
#include <math.h>

t_vector	vec_scalar(const t_vector v, double scalar)
{
	const t_vector	ret_v = \
		{.x = v.x * scalar, .y = v.y * scalar, .z = v.z * scalar};

	return (ret_v);
}

t_vector	vec_normalize(const t_vector v)
{
	const double	length = vec_length(v);
	const t_vector	ret_v = \
		{.x = v.x / length, .y = v.y / length, .z = v.z / length};

	return (ret_v);
}

double	vec_length(const t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vec_angle(const t_vector v1, const t_vector v2)
{
	return (acos(vec_dot(v1, v2)));
}
