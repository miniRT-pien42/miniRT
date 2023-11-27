#include <math.h>
#include "vector.h"
#include "scene.h"

//回転クォータニオン axisは基準となるz軸
static t_quaternion	get_rotate_quaternion(t_vector axis, double angle)
{
	t_quaternion	q_rotate;

	q_rotate.w = cos(angle / 2);
	q_rotate.x = axis.x * sin(angle / 2);
	q_rotate.y = axis.y * sin(angle / 2);
	q_rotate.z = axis.z * sin(angle / 2);
	return (q_rotate);
}

//クォータニオンの積
static t_quaternion	get_multiply_quaternion(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	q_multiply;

	q_multiply.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	q_multiply.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	q_multiply.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	q_multiply.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (q_multiply);
}

static t_vector	rotate_vector(t_vector v, t_quaternion q)
{
	const t_quaternion	q_v = {0.0, v.x, v.y, v.z};
	const t_quaternion	q_conjugate = {q.w, -q.x, -q.y, -q.z};
	const t_quaternion	q_rotate = \
		get_multiply_quaternion(get_multiply_quaternion(q, q_v), q_conjugate);

	return ((t_vector){q_rotate.x, q_rotate.y, q_rotate.z});
}

t_vector	rotate_vector_by_quaternion(\
	t_vector v, double angle, t_vector dir_n)
{
	const t_vector	axis = {0.0, 0.0, 1.0};
	t_vector		r_axis;
	t_quaternion	q_rotate;

	if (is_vector_opposite(axis, dir_n))
		return ((t_vector){v.x * -1, v.y, v.z * -1});
	r_axis = cross_product(axis, dir_n);
	q_rotate = get_rotate_quaternion(r_axis, angle);
	return (rotate_vector(v, q_rotate));
}
