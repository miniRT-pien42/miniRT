#include <math.h>

double	clipping(const double num, const double min, const double max)
{
	return (fmin(max, fmax(min, num)));
}
