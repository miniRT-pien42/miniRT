#ifndef RAY_H
# define RAY_H

# include <math.h>
# include "./vector.h"
//# include "./scene.h"
///# include "./primitive.h"

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

typedef struct s_vec_dir
{
	t_vec3	start;
	t_vec3	direction;
}	t_vec_dir;

typedef struct s_point_intersection
{
	double distance;       /* 交点までの距離 */
	t_vec3 position;    /* 交点の位置ベクトル */
	t_vec3 normal;      /* 交点における物体表面の法線ベクトル */
} t_point_intersection;

t_rgb	init_color(unsigned char r, unsigned char g, unsigned char b);
t_vec3	get_vec_ray(const t_vec_dir *ray);
//t_point_intersection *intersection_test_sphere( const t_sphere *sphere, const t_vec_dir	*ray);

#endif //RAY_H
