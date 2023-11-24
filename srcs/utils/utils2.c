#include <math.h>
#include "vector.h"

double	positive_and_min(double a, double b)
{
	if (a * b < 0)
		return (fmax(a, b));
	return (fmin(a, b));
}
