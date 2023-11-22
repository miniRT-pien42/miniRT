#include <math.h>
#include "vector.h"
#include "scene.h"

//回転クォータニオン
static t_quaternion	get_rotate_quaternion(t_vector axis, double angle)
{
	t_quaternion	q_rotate;

	q_rotate.w = cos(angle / 2);
	q_rotate.x = axis[0] * sin(angle / 2);
	q_rotate.y = axis[1] * sin(angle / 2);
	q_rotate.z = axis[2] * sin(angle / 2);
	return (q);
}

//共役クォータニオン
static t_quaternion	get_conjugate_quaternion(t_quaternion q)
{
	t_quaternion	q_conjugate;

	q_conjugate.w = q.w;
	q_conjugate.x = -q.x;
	q_conjugate.y = -q.y;
	q_conjugate.z = -q.z;
	return (q_conjugate);
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

t_vector	rotate_vector_by_quaternion(t_vector axis, double angle)
{
	const t_quaternion	q_axis = {0, axis.x, axis.y, axis.z};
	const t_quaternion	q_rotate = get_rotate_quaternion(axis, angle);
	const t_quaternion	q_conjugate = get_conjugate_quaternion(q_rotate);
	const t_quaternion	q_multiply = get_multiply_quaternion(\
							quaternion_multiply(q_rotate, q_axis), q_conjugate);

	return ((t_vector){q_multiply.x, q_multiply.y, q_multiply.z});
}
