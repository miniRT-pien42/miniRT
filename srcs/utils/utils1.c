
#include <math.h>
#include "vector.h"

double	clipping(const double num, const double min, const double max)
{
	return (fmin(max, fmax(min, num)));
}

double	convert_deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}

double	convert_rad_to_deg(double rad)
{
	return (rad * 180.0 / M_PI);
}

t_vector	*convert_pw_coordinate(t_vector *v_co, int w, int h)
{
	v_co->x /= w;
	v_co->y /= h;
	return (v_co);
}

double	clamp_f(double num, double min, double max)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}
