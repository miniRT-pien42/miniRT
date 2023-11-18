#ifndef PRIMITIVE_H
# define PRIMITIVE_H

# include <stdio.h>
# include "./vector.h"
# include "./scene.h"
# include "./ray.h"

typedef struct s_plane		t_plane;
typedef struct s_sphere		t_sphere;
typedef struct s_primitive	t_primitive;

typedef enum s_shape
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_shape;

typedef struct s_primitive
{
	t_shape		type;
	t_vec3		center;
	double		diameter;
	t_vec3		v_n_norm;
	double		height;
	t_rgb		color;
	t_primitive	*next;
}	t_primitive;

typedef struct s_plane
{
	t_vec3		center;
	t_vec3		v_n_norm;
	t_rgb		color;
	t_plane		*next;
}	t_plane;

typedef struct s_sphere
{
	t_vec3		center;
	double		diameter;
	t_rgb		color;
	t_sphere	*next;
}	t_sphere;

ssize_t	extract_closest(double *list_distance, size_t size);

#endif //PRIMITIVE_H
