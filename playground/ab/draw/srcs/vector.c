#include "vector.h"

double	vec_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// double	vec_norm(t_vector v)
// {
// 	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
// }

t_vector	vec_subtract(t_vector a, t_vector b)
{
	const t_vector	v = {a.x - b.x, a.y - b.y, a.z - b.z};

	return (v);
}
