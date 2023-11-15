#ifndef SPHERE_H
# define SPHERE_H

#include <stdio.h>
# include "../include/vector.h"
# include "../include/ray.h"

typedef struct s_sphere
{
	t_vec3	center;
	double	diameter;
	t_rgb	color;
}	t_sphere;

ssize_t	extract_closest(double *list_distance, size_t size);

#endif //SPHERE_H