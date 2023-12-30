#include "scene.h"
#include "quaternion.h"
#include <math.h>

//回転クォータニオン axisは基準となるz軸
t_quaternion	get_rotate_quaternion(t_vector axis, double angle)
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
	const t_quaternion	q_v = \
		(t_quaternion){.w = 0.0, .x = v.x, .y = v.y, .z = v.z};
	const t_quaternion	q_conjugate = \
		(t_quaternion){.w = q.w, .x = q.x, .y = -q.y, .z = q.z};
	const t_quaternion	q_rotate = \
		get_multiply_quaternion(get_multiply_quaternion(q, q_v), q_conjugate);

	return ((t_vector){.x = q_rotate.x, .y = q_rotate.y, .z = q_rotate.z});
}

t_vector	rotate_vector_by_quaternion(t_vector dir_norm, t_vector v, t_screen_info screen)
{
	if (is_vector_parallel(screen.axis, dir_norm))
		return (v);
	if (is_vector_opposite(screen.axis, dir_norm))
		return ((t_vector){.x = v.x * -1, .y = v.y, .z = v.z * -1});
	return (rotate_vector(v, screen.q_rotate));
}