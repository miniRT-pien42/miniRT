#include <math.h>
#include "vector.h"

t_vector	vec_add(const t_vector a, const t_vector b)
{
	const t_vector	ret_v = {.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};

	return (ret_v);
}

t_vector	vec_subtract(const t_vector a, const t_vector b)
{
	const t_vector	ret_v = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};

	return (ret_v);
}

double	vec_dot(const t_vector a, const t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vec_cross(const t_vector a, const t_vector b)
{
	t_vector	ret_v;

	ret_v.x = a.y * b.z - a.z * b.y;
	ret_v.y = a.z * b.x - a.x * b.z;
	ret_v.z = a.x * b.y - a.y * b.x;
	return (ret_v);
}
