#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"

typedef struct s_sphere {
	t_vector	center;
	double		r;
}	t_sphere;

typedef struct s_ray {
	t_vector	position;
	t_vector	direction;
}	t_ray;

#endif
