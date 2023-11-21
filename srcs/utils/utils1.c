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

t_vector	*map_coord(t_vector *v_coord, int w, int h)
{
	v_coord->x /= w;
	v_coord->y /= h;
	return (v_coord);
}
