#include <stdlib.h> // free
#include "display.h"
#include "error.h"
#include "mlx.h"

static void	*init_mlx_p(void)
{
	void	*mlx_p;

	mlx_p = mlx_init();
	if (mlx_p == NULL)
		error_exit(ERR_MLX);
	return (mlx_p);
}

static void	*init_win_p(void *mlx_p)
{
	void	*win_p;

	win_p = mlx_new_window(mlx_p, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (win_p == NULL)
	{
		mlx_destroy_display(mlx_p);
		free(mlx_p);
		error_exit(ERR_MLX);
	}
	return (win_p);
}

static void	init_window(t_mlx *mlxs)
{
	mlxs->display->mlx_p = init_mlx_p();
	mlxs->display->win_p = init_win_p(mlxs->display->mlx_p);
}

static void	init_image(t_mlx *mlxs)
{
	t_image	*image;

	image = mlxs->image;
	image->img = mlx_new_image(mlxs->display->mlx_p, WIN_WIDTH, WIN_HEIGHT);
	if (image->img == NULL)
	{
		mlx_destroy_window(mlxs->display->mlx_p, mlxs->display->win_p);
		mlx_destroy_display(mlxs->display->mlx_p);
		free(mlxs->display->mlx_p);
		error_exit(ERR_MLX);
	}
	image->addr = mlx_get_data_addr(image->img, \
				&image->bits_per_pixel, &image->line_length, &image->endian);
}

void	init_mlxs(t_mlx *mlxs, t_display *display, t_image *image)
{
	mlxs->display = display;
	mlxs->image = image;
	init_window(mlxs);
	init_image(mlxs);
}
