#ifndef OBJECT_H
# define OBJECT_H

# include <stdbool.h>
# include "vector.h"
# include "ray.h"
# include "color.h"

typedef struct s_sphere			t_sphere;
typedef struct s_scene			t_scene;
typedef struct s_camera			t_camera;
typedef struct s_intersection	t_intersection;

typedef struct s_sphere
{
	t_vector	center;
	double		diameter;
	t_rgb		color;
	bool		is_camera_inside;
	bool		is_light_inside;
	t_sphere	*next;
}	t_sphere;

typedef struct s_discriminant
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_discriminant;

t_sphere		*init_sphere(char *line);
bool			is_intersect_to_sphere(const double d);
t_intersection	get_nearest_object(t_vector ray, t_scene *scene);
int				convert_rgb(t_rgb color);
void			check_light_inside_sphere(\
	const t_scene *scene, t_intersection *ptr_nearest);
t_discriminant	calc_discriminant(\
	const t_vector ray, const t_vector camera_pos, const t_sphere *sphere);
double			get_valid_distance(double a, double b, bool *ptr_is_inside);
double			calc_distance_to_object(\
	t_discriminant discriminant, bool *is_inside);
bool			is_shadow_by_sphere(const t_vector shadow_ray, \
	const t_scene *scene, const t_sphere *sphere_target);
#endif
