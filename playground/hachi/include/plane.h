#ifndef PLANE_H
# define PLANE_H

# include <stdio.h>
# include "../include/vector.h"
# include "../include/ray.h"

typedef struct s_plane
{
	t_vec3	center;
	t_vec3	v_n_norm;
	t_rgb	color;
}	t_plane;

#endif //PLANE_H
