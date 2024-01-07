#include "camera.h"
#include "display.h"
#include "object.h"
#include "ray.h"
#include "scene.h"
#include <stddef.h>

static t_vector	set_screen_to_camera_pos(\
	t_vector coord_on_screen, t_screen_info screen)
{
	coord_on_screen = rotate_vector_x(coord_on_screen, -screen.rotate_x);
	coord_on_screen = rotate_vector_y(coord_on_screen, screen.rotate_y);
	coord_on_screen = vec_add(coord_on_screen, screen.center_screen);
	return (coord_on_screen);
}

static t_ray	calc_ray(t_scene *scene, t_screen_info screen)
{
	t_ray			ray;
	t_vector		coord_on_screen;

	ray.position = scene->camera->pos;
	coord_on_screen.x = (2.0 * screen.x) / (WIDTH - 1) - 1.0;
	coord_on_screen.y = 0.0;
	coord_on_screen.z = -(2.0 * HEIGHT / WIDTH * screen.y) / (HEIGHT - 1) + 1.0;
	coord_on_screen = set_screen_to_camera_pos(coord_on_screen, screen);
	ray.direction = vec_subtract(coord_on_screen, scene->camera->pos);
	return (ray);
}

void	set_each_pixel_color(\
	const t_mlx *mlxs, t_scene *scene, t_screen_info screen)
{
	int			color;
	const t_ray	ray = calc_ray(scene, screen);
	void		*nearest_object;

	nearest_object = NULL;
	if (scene->camera->fov > 0 && scene->camera->fov < 180)
		nearest_object = get_nearest_object(&ray, scene->list_object);
	if (nearest_object == NULL)
		color = COLOR_BLUE;
	else
		color = convert_rgb(ray_tracing(scene, nearest_object, &ray));
	my_mlx_pixel_put(mlxs->image, screen.y, screen.x, color);
}
