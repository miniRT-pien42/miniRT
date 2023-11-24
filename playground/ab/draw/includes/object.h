#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"

typedef struct s_sphere {
	t_vector	center;
	double		r;
}	t_sphere;

typedef struct s_cylinder {
	t_vector	center; // 中心座標ベクトル
	t_vector	axis_normal; // 法線ベクトル
	double		r;
	double		height;
}	t_cylinder;

typedef struct s_ray {
	t_vector	position;
	t_vector	direction;
}	t_ray;

/* ray */
t_ray	calc_ray(const int y, const int x);

#endif
