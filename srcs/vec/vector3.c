#include "helpers.h"
#include <math.h>

//2つの正規化ベクトルが並行で逆方向か判定
bool	is_vector_opposite(t_vector a, t_vector b)
{
	return (fabs(vec_dot(a, b) + 1.0) < EPSILON);
}
