#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
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
t_intersection	get_nearest_object(t_vector ray, t_scene *scene);
int				convert_rgb(t_rgb color);
#endif
