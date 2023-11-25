#include <math.h>
#include <stdlib.h>
#include "display.h"
#include "scene.h"
#include "ray.h"

// screen上の点の位置
static t_vector	calc_ray_direction(const int y, const int x)
{
	const double	screen_x = (2.0 * x) / (WIDTH - 1) - 1.0;
	const double	screen_y = -(2.0 * y) / (HEIGHT - 1) + 1.0;
	const double	screen_z = 0.0;
	const t_vector	ray_direction = {screen_x, screen_y, screen_z};

	return (ray_direction);
}

void	set_each_pixel_color(\
	t_mlx *mlxs, const int y, const int x, t_scene *scene)
{
	int				color;
	t_vector		ray;
	t_intersection	nearest;

	ray = vec_subtract(calc_ray_direction(y, x), scene->camera->pos);
	nearest = get_nearest_object(ray, scene);
	if (nearest.distance == INFINITY)
		color = COLOR_BLUE;
	else
		color = convert_rgb(ray_tracing(scene, nearest, ray));
	my_mlx_pixel_put(mlxs->image, y, x, color);
}
