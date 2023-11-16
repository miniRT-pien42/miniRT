#ifndef PRIMITIVE_H
# define PRIMITIVE_H

# include <stdio.h>
# include "./vector.h"
# include "./scene.h"
# include "./ray.h"

typedef struct s_plane		t_plane;
typedef struct s_sphere		t_sphere;
typedef struct s_cylinder	t_cylinder;

typedef struct s_plane
{
	t_vec3	center;
	t_vec3	v_n_norm;
	t_rgb	color;
	double	k_a;
	t_plane	*next;
}	t_plane;

typedef struct s_sphere
{
	t_vec3		center;
	double		diameter;
	t_rgb		color;
	double		k_a;
	t_sphere	*next;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		v_n_norm;
	double		diameter;
	double		height;
	t_rgb		color;
	double		k_a;
	t_cylinder	*next;
}	t_cylinder;

ssize_t	extract_closest(double *list_distance, size_t size);

#endif //PRIMITIVE_H
