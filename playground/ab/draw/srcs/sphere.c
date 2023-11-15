#include "color.h"
#include "display.h"
#include "vector.h"

const t_sphere	sphere = {{0, 0, 5}, 1.0};
const t_vector	view = {0, 0, -5};

static t_ray	calc_ray(const int y, const int x)
{
	const double	screen_y = 1.0 - (2.0 * y) / (WIN_HEIGHT - 1);
	const double	screen_x = (2.0 * x) / (WIN_WIDTH - 1) - 1.0;
	const t_vector	ray_direction = {screen_x, screen_y, 5};
	const t_ray		ray = {view, ray_direction};

	return (ray);
}

static bool	is_intersect_sphere(t_ray ray, t_sphere sphere)
{
	const t_vector	v = vec_subtract(ray.position, sphere.center);
	const double	a = vec_dot(ray.direction, ray.direction);
	const double	b = 2.0 * vec_dot(v, ray.direction);
	const double	c = vec_dot(v, v) - sphere.r * sphere.r;
	const double	discriminant = b * b - 4 * a * c;

	return (discriminant > 0);
}

void	set_each_pixel_color(t_mlx *mlxs, const int y, const int x)
{
	t_ray	ray;
	int		color;

	ray = calc_ray(y, x);
	if (is_intersect_sphere(ray, sphere))
		color = COLOR_RED;
	else
		color = COLOR_BLUE;
	my_mlx_pixel_put(mlxs->image, y, x, color);
}
