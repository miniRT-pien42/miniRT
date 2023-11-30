#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "object.h"

# define NO_INTERSECTION	(-1)

typedef struct s_ray
{
	t_vector	position;
	t_vector	direction;
}	t_ray;

typedef struct s_intersection
{
	t_sphere	*sphere;
	double		distance;
	t_vector	position;
	t_vector	normal;
	t_vector	incident;
}	t_intersection;

#endif
