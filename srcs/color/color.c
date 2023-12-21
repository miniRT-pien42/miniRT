#include "ray.h"

int	convert_rgb(t_rgb color)
{
	return ((color.r << RED_SHIFT) | (color.g << GREEN_SHIFT) | color.b);
}
