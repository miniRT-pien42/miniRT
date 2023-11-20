
#include <math.h>
#include "../../include/vector.h"

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


double	get_scalar(const t_vector v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}
