#ifndef RAY_H
# define RAY_H

# include <math.h>
# include "./vector.h"
//# include "./scene.h"
//# include "./primitive.h"

typedef struct s_scene		t_scene;
typedef struct s_sphere		t_sphere;

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

typedef struct s_point
{
	double distance;       /* 交点までの距離 */
	t_vec3 position;    /* 交点の位置ベクトル */
	t_vec3 normal;      /* 交点における物体表面の法線ベクトル */
	t_vec3 incident;       /* 入射光線ベクトル */
} t_point;

t_rgb	init_color(unsigned char r, unsigned char g, unsigned char b);
t_vec3	get_vec_ray(const t_vec_dir *ray);
t_vec3	get_vec_ray_norm(const t_vec_dir *ray);
t_vec3	get_vec_ray_sd(const t_vec3 start, const t_vec3 direction);
t_vec3	get_vec_ray_sd_norm(const t_vec3 start, const t_vec3 direction);
t_point	*intersection_ray_sphere(\
	const t_sphere *sphere, const t_vec3 vec_ray, \
	const t_vec3 vec_sphere_to_eye);
t_rgb	raytrace(\
	const t_scene *scene, const t_vec3 *vec_ray, const t_vec3 *vec_sphere_to_eye);
#endif //RAY_H
