#include <math.h>
#include "vector.h"
#include "ray.h"
#include "object.h"
#include "color.h"

int	convert_rgb(t_rgb color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
	return ((color.r << RED_SHIFT) | (color.g << GREEN_SHIFT) | color.b);
