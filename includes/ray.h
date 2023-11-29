#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "object.h"

typedef struct s_ray
{
	t_vector	position;
	t_vector	direction;
}	t_ray;

typedef struct s_intersection
{
	void		*object;
	double		distance;
	t_vector	position;
	t_vector	normal;
	t_vector	incident;
}	t_intersection;

#endif
