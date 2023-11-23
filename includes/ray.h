#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "object.h"

typedef struct s_ray
{
	t_vector	position;
	t_vector	direction;
}	t_ray;

typedef struct s_intersection
{
	t_sphere	*sphere;//交差したsphere(要らないかも？)
	double		distance;// 交点までの距離
	t_vector	position;//交点の位置ベクトル
	t_vector	normal;//交点における物体表面の法線ベクトル
	t_vector	incident;//入射光線ベクトル
}	t_intersection;

typedef struct s_point
{
	t_sphere	*sphere;
	double		distance;       /* 交点までの距離 */
	t_vector		position;    /* 交点の位置ベクトル */
	t_vector		normal;      /* 交点における物体表面の法線ベクトル */
	t_vector		incident;       /* 入射光線ベクトル */
}	t_point;

#endif
