#include "mlx.h"
#include "scene.h"
#include "vector.h"
#include <stdlib.h> // exit
#include <X11/X.h> // mlx_hook

void	my_mlx_pixel_put(\
					t_image *image, const int y, const int x, const int color)
{
	char	*dst;
	int		offset;

	offset = y * image->line_length + x * (image->bits_per_pixel / 8);
	dst = image->addr + offset;
	*(unsigned int *)dst = color;
}

static t_screen_info	get_screen_info(t_scene *scene)
{
	t_screen_info	screen;
	double			rotation_angle;
	t_vector		r_axis;

	screen.axis = set_axis_base();
	screen.center_screen = get_center_screen(scene->camera);
	rotation_angle = \
		get_angle(set_axis_base(), scene->camera->dir_norm);
	r_axis = vec_normalize(vec_cross(screen.axis, scene->camera->dir_norm));
	screen.q_rotate = get_rotate_quaternion(r_axis, rotation_angle);
	return (screen);
}

static void	set_image(t_mlx *mlxs, t_scene *scene)
{
	t_screen_info	screen = get_screen_info(scene);

	screen.y = 0;
	while (screen.y < HEIGHT)
	{
		screen.x = 0;
		while (screen.x < WIDTH)
		{
			set_each_pixel_color(mlxs, scene, screen);
			screen.x++;
		}
		screen.y++;
	}
	mlx_put_image_to_window(\
			mlxs->display->mlx_p, mlxs->display->win_p, mlxs->image->img, 0, 0);
}

static int	close_window(const t_mlx *mlxs)
{
	mlx_destroy_image(mlxs->display->mlx_p, mlxs->image->img);
	mlx_destroy_window(mlxs->display->mlx_p, mlxs->display->win_p);
	mlx_destroy_display(mlxs->display->mlx_p);
	free(mlxs->display->mlx_p);
	destroy_scene(mlxs->scene);
	exit(EXIT_SUCCESS);
	return (UNREACHABLE);
}

static void	set_hook(t_mlx *mlxs)
{
	void	*win_p;
	void	*params;

	win_p = mlxs->display->win_p;
	params = (void *)mlxs;
	mlx_hook(win_p, DestroyNotify, StructureNotifyMask, close_window, params);
}

void	display(t_scene *scene)
{
	t_mlx		mlxs;
	t_display	display;
	t_image		image;

	init_mlxs(&mlxs, &display, &image, scene);
	set_image(&mlxs, scene);
	set_hook(&mlxs);
	mlx_loop(mlxs.display->mlx_p);
}
