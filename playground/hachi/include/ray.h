#ifndef RAY_H
# define RAY_H

# include <math.h>
# include "./vector.h"

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

typedef struct s_ray
{
	t_vec3	start;
	t_vec3	direction;
}	t_ray;

t_rgb	init_color(unsigned char r, unsigned char g, unsigned char b);

#endif //RAY_H
