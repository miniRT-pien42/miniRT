#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
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

t_deque			*init_object(void);
t_sphere		*init_sphere(void);
t_sphere		*init_sphere2_tmp(void);
t_sphere		*init_sphere3_tmp(void);
t_plane			*init_plane();
t_shape			get_object_type(void *object);
t_intersection	get_nearest_object(t_vector ray, t_scene *scene);
void			update_nearest_sphere(t_vector ray, t_scene *scene, \
	t_sphere *sphere, t_intersection *ptr_nearest);
void			update_nearest_plane(t_vector ray, t_scene *scene, \
	t_plane *plane, t_intersection *ptr_nearest);
int				convert_rgb(t_rgb color);

/* sphere*/
void			add_to_list_object(t_scene *scene, const char **line);

#endif
