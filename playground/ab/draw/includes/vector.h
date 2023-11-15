#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdbool.h>

typedef struct s_vector {
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ray {
	t_vector	position;
	t_vector	direction;
}	t_ray;

typedef struct s_sphere {
	t_vector	center;
	double		r;
}	t_sphere;

double		vec_dot(t_vector a, t_vector b);
t_vector	vec_subtract(t_vector a, t_vector b);

#endif
