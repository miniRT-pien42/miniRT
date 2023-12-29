#include "helpers.h"
#include <math.h>

//2つの正規化ベクトルが並行で逆方向か判定
bool	is_vector_opposite(t_vector a, t_vector b)
{
	return (fabs(vec_dot(a, b) + 1.0) < EPSILON);
}

//2つの正規化ベクトルの向きがほぼ一致するか判定
bool	is_vector_parallel(t_vector a, t_vector b)
{
	if (fabs(a.x - b.x) < EPSILON && fabs(a.y - b.y) < EPSILON && fabs(a.z - b.z) < EPSILON)
		return (true);
	return (false);
}
