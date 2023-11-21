#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"

typedef struct s_sphere {
	t_vector	center;
	double		r;
}	t_sphere;

typedef struct s_ray {
	t_vector	position;
	t_vector	direction;
}	t_ray;

typedef struct s_material {
	double	ambient; // 環境光反射係数 ka
	double	diffuse; // 拡散反射係数 kd
}	t_material;

typedef struct s_scene {
	double		light_ambient;	// 環境光の照度 Ea
	double		light_diffuse;	// 直接光の照度 Ei
	t_vector	light_pos;
	t_vector	view;
	t_material	material;
}	t_scene;

#endif
