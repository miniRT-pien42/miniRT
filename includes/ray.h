#ifndef RAY_H
# define RAY_H

# include "object.h"
# include "light.h"

# define NO_INTERSECTION	(-1)

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
	double		l_dot;
}	t_intersection;

// ray/ray.c
bool	is_shadow_plane(t_scene *scene, t_intersection intersection);
double	get_l_dot(t_intersection intersection);
t_rgb_f	get_lux_ambient(const t_light_ambient *ambient);
t_rgb_f	get_lux_light(const t_light *light, t_rgb color, double l_dot);
t_rgb_f	get_lux_total(t_rgb_f lux_ambient, t_rgb_f lux_light);

#endif
