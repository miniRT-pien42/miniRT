#include <math.h>
#include <stdlib.h>
#include "display.h"
#include "scene.h"
#include "ray.h"

// screen上の点の位置
static t_vector	calc_ray_direction(const int y, const int x, t_scene *scene)
{
	t_vector		coord_on_screen;

	coord_on_screen.x = (2.0 * x) / (WIDTH - 1) - 1.0;
	coord_on_screen.y = -(2.0 * HEIGHT / WIDTH * y) / (HEIGHT - 1) + 1.0;
	coord_on_screen.z = 0.0;
	coord_on_screen = \
		rotate_vector_by_quaternion(\
			coord_on_screen, scene->rotation_angle, scene->camera->dir_n);
	coord_on_screen = vec_add(coord_on_screen, scene->center_screen);
	return (vec_subtract(coord_on_screen, scene->camera->pos));
}

void	set_each_pixel_color(\
	t_mlx *mlxs, const int y, const int x, t_scene *scene)
{
	int				color;
	t_vector		ray;
	t_intersection	nearest;

	ray = calc_ray_direction(y, x, scene);
	nearest = get_nearest_object(ray, scene);
	if (nearest.distance == INFINITY)
		color = COLOR_BLUE;
	else
	{
		if (get_object_type(nearest.object) == SPHERE)
			color = convert_rgb(ray_tracing(scene, nearest, ray));
		else if (get_object_type(nearest.object) == PLANE)
			color = convert_rgb(((t_plane *)nearest.object)->color);
		else
			color = COLOR_RED;
	}
	my_mlx_pixel_put(mlxs->image, y, x, color);
}
