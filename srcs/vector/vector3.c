#include "helpers.h"
#include "vector.h"
#include <math.h>

bool	is_vector_opposite(t_vector a, t_vector b)
{
	return (fabs(vec_dot(a, b) + 1.0) < EPSILON);
}

bool	is_vector_parallel(t_vector a, t_vector b)
{
	if (fabs(a.x - b.x) < EPSILON && \
		fabs(a.y - b.y) < EPSILON && \
		fabs(a.z - b.z) < EPSILON)
		return (true);
	return (false);
}
