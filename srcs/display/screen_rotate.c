#include "display.h"
#include <math.h>

static bool	is_parallel_or_opposite(t_vector v, double *angle)
{
	const t_vector	base = set_axis_base();

	if (is_vector_parallel(v, base))
	{
		*angle = 0.0;
		return (true);
	}
	if (is_vector_opposite(v, base))
	{
		*angle = M_PI;
		return (true);
	}
	return (false);
}

double	get_rotate_x(t_vector direction)
{
	double	angle;
	const t_vector	rotate_base = set_axis_base();

	if (is_parallel_or_opposite(direction, &angle))
		return (angle);
	angle = vec_angle(direction, rotate_base);
	return (angle);
}

double	get_rotate_y(t_vector direction)
{
	double		angle;
	t_vector	dir_norm;
	t_vector	cross;
	const t_vector	rotate_base = set_axis_rotate_base();

	if (is_parallel_or_opposite(direction, &angle))
		return (angle);
	dir_norm = (t_vector){.x = direction.x, .y = 0, .z = direction.z};
	dir_norm = vec_normalize(dir_norm);
	cross = vec_cross(dir_norm, rotate_base);
	angle = vec_angle(dir_norm, rotate_base);
	if (cross.y > 0)
		return (angle * -1);
	return (angle);
}

t_vector	rotate_vector_x(t_vector v, const double angle)
{
	t_vector	v_rotate;

	v_rotate.x = v.x;
	v_rotate.y = v.y * cos(angle) - v.z * sin(angle);
	v_rotate.z = v.y * sin(angle) + v.z * cos(angle);
	return (v_rotate);
}

t_vector	rotate_vector_y(t_vector v, const double angle)
{
	t_vector	v_rotate;

	v_rotate.x = v.x * cos(angle) + v.z * sin(angle);
	v_rotate.y = v.y;
	v_rotate.z = -v.x * sin(angle) + v.z * cos(angle);
	return (v_rotate);
}
