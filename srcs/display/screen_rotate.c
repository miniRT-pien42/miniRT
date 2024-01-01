#include "display.h"
#include "helpers.h"
#include <math.h>

static bool	is_parallel_or_opposite(t_vector v1, t_vector v2, double *angle)
{
	if (is_vector_parallel(v1, v2))
	{
		*angle = convert_deg_to_rad(0);
		return (true);
	}
	if (is_vector_opposite(v1, v2))
	{
		*angle = convert_deg_to_rad(180);
		return (true);
	}

	return (false);
}

double	get_rotate_x(t_vector direction, const t_vector base)
{
	double			angle;

	if (is_parallel_or_opposite(direction, base, &angle))
		return (angle);
	angle = vec_angle(direction, base);
	return (angle);
}

double	get_rotate_y(\
	t_vector direction, const t_vector base, const t_vector rotate_base)
{
	double			angle;
	t_vector		dir_norm;
	t_vector		cross;

	if (is_parallel_or_opposite(direction, base, &angle))
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
