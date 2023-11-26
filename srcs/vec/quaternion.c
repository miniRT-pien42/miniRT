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

//todo: vは回転対象のスクリーン座標、angleにはaxis（Z軸）とカメラ方向の回転ラジアンが入っている
t_vector	rotate_vector_by_quaternion(t_vector v, double angle)
{
	const t_quaternion	q_v = {0, v.x, v.y, v.z};
	const t_quaternion	q_rotate = get_rotate_quaternion((t_vector){0, 0, 1}, angle);
	const t_quaternion	q_conjugate = get_conjugate_quaternion(q_rotate);
	const t_quaternion	q_multiply = get_multiply_quaternion(\
		get_multiply_quaternion(q_rotate, q_v), q_conjugate);

	return ((t_vector){q_multiply.x, q_multiply.y, q_multiply.z});
}
