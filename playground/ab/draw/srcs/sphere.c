#include <math.h>
#include <stdio.h> // todo: erase
#include "color.h"
#include "display.h"
#include "object.h"
#include "utils.h"
#include "vector.h"

const t_sphere	sphere = {{0, 0, 5}, 1.0};
const t_vector	view = {0, 0, -5};
const t_vector	light_pos = {-5, 5, -5};
const t_scene	scene = {0.1, 1.0, light_pos, view, {0.01, 0.69}};

static t_ray	calc_ray(const int y, const int x)
{
	const double	screen_y = 1.0 - (2.0 * y) / (WIN_HEIGHT - 1);
	const double	screen_x = (2.0 * x) / (WIN_WIDTH - 1) - 1.0;
	const t_vector	ray_direction = {screen_x, screen_y, 5};
	const t_ray		ray = {view, ray_direction};

	return (ray);
}

// 二次方程式のうち 正 && 小さい方 を返す
static double	calc_param_t(const t_ray ray)
{
	const t_vector	v = vec_subtract(ray.position, sphere.center);
	const double	a = vec_dot(ray.direction, ray.direction);
	const double	b = 2.0 * vec_dot(v, ray.direction);
	const double	c = vec_dot(v, v) - sphere.r * sphere.r;
	const double	discriminant = b * b - 4 * a * c;
	double			t1;
	double			t2;

	if (discriminant < 0)
		return (-1.0); // 解なし
	if (discriminant == 0)
		return (-b * (2 * a));
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);
	if (0 <= t1 && t1 < t2)
		return (t1);
	else
		return (t2);
}

static int	calc_pixel_color(const t_vector color)
{
	const int	red = (int)(color.x * 255);
	const int	green = (int)(color.y * 255);
	const int	blue = (int)(color.z * 255);

	return ((red << RED_SHIFT) | (green << GREEN_SHIFT) | blue);
}

static t_vector	calc_object_color(const t_ray ray, const double t)
{
	const t_vector	intersect_point = vec_add(ray.position, vec_scalar(ray.direction, t));
	const t_vector	light_v = vec_normalize(vec_subtract(light_pos, intersect_point));
	const t_vector	normal = vec_normalize(vec_subtract(intersect_point, sphere.center));
	const double	dot_normal_and_light = clipping(vec_dot(normal, light_v), 0.0, 1.0);
	const double	light_ambient = scene.material.ambient * scene.light_ambient;
	const double	light_diffuse = scene.material.diffuse * scene.light_diffuse * dot_normal_and_light;
	const double	color = clipping(light_ambient + light_diffuse, 0.0, 1.0);

	return ((t_vector){color, color, color});
}

void	set_each_pixel_color(t_mlx *mlxs, const int y, const int x)
{
	const t_ray		ray = calc_ray(y, x);
	const double	t = calc_param_t(ray);
	t_vector		total_color;
	int				color;

	// background
	if (t <= 0)
		color = COLOR_BLUE;
	else
	{
		total_color = calc_object_color(ray, t);
		printf("RGB=(%f,%f,%f)\n", total_color.x, total_color.y, total_color.z);
		color = calc_pixel_color(total_color);
	}
	my_mlx_pixel_put(mlxs->image, y, x, color);
}
