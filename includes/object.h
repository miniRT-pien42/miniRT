#ifndef OBJECT_H
# define OBJECT_H

# include <stdbool.h>
# include "vector.h"
# include "color.h"

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
	t_shape		shape;
	t_vector	center;
	double		diameter;
	t_rgb		color;
	void		*next;
}	t_sphere;

typedef struct s_plane
{
	t_shape		shape;
	t_vector	point;
	t_vector	dir_n;
	t_rgb		color;
	void		*next;
}	t_plane;

typedef struct s_discriminant
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_discriminant;

void			*init_object(char *line);
t_sphere		*init_sphere(char *line);
t_plane			*init_plane(char *line);
void			judge_nearest_sphere(t_vector ray, t_scene *scene, \
	t_sphere *sphere, t_intersection *ptr_nearest);
void			judge_nearest_plane(t_vector ray, t_scene *scene, \
	t_plane *plane, t_intersection *ptr_nearest);
t_intersection	get_nearest_object(t_vector ray, t_scene *scene);
int				convert_rgb(t_rgb color);
#endif
