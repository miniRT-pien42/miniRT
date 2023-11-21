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

static void	set_image(t_mlx *mlxs)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			set_each_pixel_color(mlxs, y, x);
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

void	display(void)
{
	t_mlx		mlxs;
	t_display	display;
	t_image		image;

	init_mlxs(&mlxs, &display, &image);
	set_image(&mlxs);
	set_hook(&mlxs);
	mlx_loop(mlxs.display->mlx_p);
}
