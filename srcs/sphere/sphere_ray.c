#include <math.h>
#include "vector.h"
#include "display.h"
#include "scene.h"

// screen上の点の位置
static t_vector	calc_ray_direction(const int y, const int x)
{
	const double	screen_x = (2.0 * x) / (WIDTH - 1) - 1.0;
	const double	screen_y = -(2.0 * y) / (HEIGHT - 1) + 1.0;
	const double	screen_z = 0.0;
	const t_vector	ray_direction = {screen_x, screen_y, screen_z};

	return (ray_direction);
}

// 解の方程式
static double	calc_discriminant(const t_vector eye_v, t_scene *scene)
{
	const t_sphere	*sphere = scene->list_sphere;
	const t_vector	v = vec_subtract(scene->camera->pos, sphere->center);
	const double	a = pow(get_scalar(eye_v), 2);
	const double	b = 2.0 * vec_dot(eye_v, v);
	const double	c = pow(get_scalar(v), 2) - pow(sphere->diameter / 2, 2);

	return (pow(b, 2) - 4 * a * c);
}

// cameraからのrayとsphereとの衝突判定
bool	is_intersect_to_sphere(const int y, const int x, t_scene *scene)
{
	const t_vector	ray_direction = calc_ray_direction(y, x);
	const t_vector	eye_v = vec_subtract(ray_direction, scene->camera->pos);
	const double	discriminant = calc_discriminant(eye_v, scene);

	return (discriminant > 0);
}
