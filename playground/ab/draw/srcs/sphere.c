#include <math.h>
#include <stdio.h> // todo: erase
#include "color.h"
#include "display.h"
#include "object.h"
#include "vector.h"

const t_sphere	sphere = {{0, 0, 5}, 1.0};
const t_vector	view = {0, 0, -5};
const t_vector	light = {-5, 5, -5};

static t_ray	calc_ray(const int y, const int x)
{
	const double	screen_y = 1.0 - (2.0 * y) / (WIN_HEIGHT - 1);
	const double	screen_x = (2.0 * x) / (WIN_WIDTH - 1) - 1.0;
	const t_vector	ray_direction = {screen_x, screen_y, 5};
	const t_ray		ray = {view, ray_direction};

	return (ray);
}

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
		return (-1.0);
	if (discriminant == 0)
		return (-b * (2 * a));
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);
	if (0 <= t1 && t1 < t2)
		return (t1);
	else
		return (t2);
}

static int	calc_color(const int color)
{
	int	red;
	int	green;
	int	blue;

	red = (color >> RED_SHIFT) & COLOR_MASK;
	green = (color >> GREEN_SHIFT) & COLOR_MASK;
	blue = (color & COLOR_MASK);
	return ((red << RED_SHIFT) | (green << GREEN_SHIFT) | blue);
}

static int	calc_object_color(const t_ray ray, const double t)
{
	const t_vector	intersect_point = vec_add(ray.position, vec_scalar(ray.direction, t));
	const t_vector	light_v = vec_normalize(vec_subtract(light, intersect_point));
	const t_vector	normal = vec_normalize(vec_subtract(intersect_point, sphere.center));
	const double	dot_normal_and_light = fmax(0, vec_dot(normal, light_v));
	const int		color = calc_color((int)(dot_normal_and_light * 255));

	return (color);
}

void	set_each_pixel_color(t_mlx *mlxs, const int y, const int x)
{
	const t_ray		ray = calc_ray(y, x);
	const double	t = calc_param_t(ray);
	int				color;

	// background
	if (t <= 0)
		color = COLOR_BLUE;
	else
	{
		color = calc_object_color(ray, t);
		if (color != 0)
			printf("RGB=(%d,%d,%d)\n", color, color, color);
	}
	my_mlx_pixel_put(mlxs->image, y, x, color);
}
