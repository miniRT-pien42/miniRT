#ifndef RAY_H
# define RAY_H

# include "scene.h"
# include "vector.h"
# include "object.h"

typedef struct s_sphere	t_sphere;
typedef struct s_scene	t_scene;

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

t_rgb	ray_tracing(const t_scene *scene, t_intersection nearest, t_vector ray);

#endif
