#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"
# include "color.h"
# include "ft_deque.h"

typedef struct s_sphere			t_sphere;
typedef struct s_scene			t_scene;
typedef struct s_camera			t_camera;
typedef struct s_intersection	t_intersection;

typedef enum s_shape
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_shape;

typedef struct s_sphere
{
	t_shape		type;
	t_vector	center;
	double		diameter;
	t_rgb		color;
	bool		is_camera_inside;
	bool		is_light_inside;
	t_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	t_shape		type;
	t_vector	point;
	t_vector	dir_n;
	t_rgb		color;
}	t_plane;

typedef struct s_discriminant
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_discriminant;

t_deque			*init_object(char *line);
t_sphere		*init_sphere(char *line);
bool			is_intersect_to_sphere(const double d);
t_sphere		*init_sphere2_tmp(void);
t_sphere		*init_sphere3_tmp(void);
t_plane			*init_plane(char *line);
t_shape			get_object_type(void *object);
void			update_nearest_sphere(t_vector ray, t_scene *scene, \
	t_sphere *sphere, t_intersection *ptr_nearest);
void			update_nearest_plane(t_vector ray, t_scene *scene, \
	t_plane *plane, t_intersection *ptr_nearest);
t_intersection	get_nearest_object(t_vector ray, t_scene *scene);
int				convert_rgb(t_rgb color);
void			check_light_inside_sphere(\
	const t_scene *scene, t_intersection *ptr_nearest);
t_discriminant	calc_discriminant(\
	const t_vector ray, const t_vector camera_pos, const t_sphere *sphere);
double			calc_distance_to_object(\
	t_discriminant discriminant, bool *is_inside, bool is_abs);
bool			is_shadow_by_sphere(const t_vector shadow_ray, \
	const t_scene *scene, const t_sphere *sphere_target);
#endif
