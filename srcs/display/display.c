#include <stddef.h>
#include <stdlib.h> // exit
#include <X11/X.h> // mlx_hook
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

static void	set_image(t_mlx *mlxs, t_scene *scene)
{
	size_t	y;
	size_t	x;

	(void) scene;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			//todo: set_each_pixel_colorを#5,#6,#8で実装
			set_each_pixel_color(mlxs, y, x, scene);
			//todo: #5 交差判定（sphere）交差しない=>背景色
			//todo: #6 nearestの情報取得(sphere)
			//todo: #8 描画色取得(shadow-ray判定含む)
			x++;
		}
		y++;
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

	init_mlxs(&mlxs, &display, &image);
	set_image(&mlxs, scene);
	set_hook(&mlxs);
	mlx_loop(mlxs.display->mlx_p);
}
