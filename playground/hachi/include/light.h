#ifndef LIGHT_H
# define LIGHT_H

# include <math.h>
# include "./vector.h"
# include "./ray.h"

typedef struct s_light
{
	t_vec3	pos;
	double	e_a; /* 照度 */
}	t_light;

typedef struct s_light_ambient
{
	double e_a; /* 照度 */
	t_rgb color;
}	t_light_ambient;

#endif //LIGHT_H
