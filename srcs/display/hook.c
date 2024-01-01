#include "display.h"
#include "mlx.h"
#include "scene.h"
#include <stdlib.h> // exit
#include <X11/keysym.h> // XK_Escape
#include <X11/X.h> // mlx_hook

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

static int	key_hook(const int keycode, t_mlx *mlxs)
{
	if (keycode == XK_Escape)
		close_window(mlxs);
	return (KEY_NONE);
}

void	set_hook(t_mlx *mlxs)
{
	void	*win_p;
	void	*params;

	win_p = mlxs->display->win_p;
	params = (void *)mlxs;
	mlx_hook(win_p, KeyPress, KeyPressMask, key_hook, params);
	mlx_hook(win_p, DestroyNotify, StructureNotifyMask, close_window, params);
}
