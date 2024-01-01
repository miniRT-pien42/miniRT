#include "display.h"
#include "helpers.h"
#include <math.h>

double	get_rotate_x(t_vector direction)
{
	double			angle;
	const t_vector	base = vec_scalar(set_axis_base(), -1);

	if (is_vector_parallel(direction, base))
		return (convert_deg_to_rad(0));
	if (is_vector_opposite(direction, base))
		return (convert_deg_to_rad(180));
	angle = convert_rad_to_deg(vec_angle(direction, base));
	return (convert_deg_to_rad(angle));
}

double	get_rotate_y(t_vector direction)
{
	t_vector		dir_norm;
	t_vector		cross;
	const t_vector	base = set_axis_base();
	const t_vector	rotate_base = set_axis_rotate_base();

	if (is_vector_parallel(direction, base))
		return (convert_deg_to_rad(0));
	if (is_vector_opposite(direction, base))
		return (convert_deg_to_rad(180));
	dir_norm = (t_vector){.x = direction.x, .y = 0, .z = direction.z};
	dir_norm = vec_normalize(dir_norm);
	cross = vec_cross(dir_norm, rotate_base);
	if (cross.y < 0)
		return (vec_angle(dir_norm, rotate_base) * -1);
	return (vec_angle(dir_norm, rotate_base));
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
