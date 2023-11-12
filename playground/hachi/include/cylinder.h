#ifndef CYLINDER_H
# define CYLINDER_H

#include <stdio.h>
# include "../include/vector.h"
# include "../include/ray.h"

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	v_n_norm;
	double	diameter;
	double	height;
	t_rgb	color;
}	t_cylinder;

ssize_t	extract_closest(double *list_distance, size_t size);

#endif //CYLINDER_H
