#include "display.h"
#include "mlx.h"

void	my_mlx_pixel_put(\
	t_image *image, const int y, const int x, const int color)
{
	char	*dst;
	int		offset;

	offset = y * image->line_length + x * (image->bits_per_pixel / 8);
	dst = image->addr + offset;
	*(unsigned int *)dst = color;
}

void	set_image(const t_mlx *mlxs)
{
	t_screen_info	screen;
	t_scene			*scene;

	scene = mlxs->scene;
	screen = get_screen_info(scene);
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

void	display(t_scene *scene)
{
	t_mlx		mlxs;
	t_display	display;
	t_image		image;

	init_mlxs(&mlxs, &display, &image, scene);
	set_image(&mlxs);
	set_hook(&mlxs);
	mlx_loop(mlxs.display->mlx_p);
}
