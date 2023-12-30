#ifndef RAY_H
# define RAY_H

# include "light.h"
# include "vector.h"

# define NO_INTERSECTION	(-1)
# define NOT_ILLUMINATED	(-1)

typedef struct s_scene	t_scene;

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
	double		l_dot;
}	t_intersection;

// ray/ray.c
double	get_l_dot(t_scene *scene, t_intersection intersection);
t_rgb_f	get_lux_ambient(const t_light_ambient *ambient);
t_rgb_f	get_lux_light(const t_light *light, void *nearest_object, double l_dot);
t_rgb_f	add_up_lux_total(t_rgb_f lux_ambient, t_rgb_f lux_light);

#endif
