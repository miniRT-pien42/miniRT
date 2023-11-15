#include "vector.h"

t_vector	vec_add(const t_vector a, const t_vector b)
{
	const t_vector	ret_v = {a.x + b.x, a.y + b.y, a.z + b.z};

	return (ret_v);
}

t_vector	vec_subtract(const t_vector a, const t_vector b)
{
	const t_vector	ret_v = {a.x - b.x, a.y - b.y, a.z - b.z};

	return (ret_v);
}

double	vec_norm(const t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vec_dot(const t_vector a, const t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vec_scalar(const t_vector v, double scalar)
{
	const t_vector	ret_v = {v.x * scalar, v.y * scalar, v.z * scalar};

	return (ret_v);
}

t_vector	vec_normalize(const t_vector v)
{
	const double	length = vec_norm(v);
	const t_vector	ret_v = {v.x / length, v.y / length, v.x / length};

	return (ret_v);
}
