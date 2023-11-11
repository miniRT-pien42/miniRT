
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/ray.h"

t_rgb	init_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_rgb	color_return;

	color_return.r = r;
	color_return.g = g;
	color_return.b = b;
	return (color_return);
}
