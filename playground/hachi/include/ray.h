#ifndef RAY_H
# define RAY_H

# include <math.h>

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

t_rgb	init_color(unsigned char r, unsigned char g, unsigned char b);

#endif //RAY_H
