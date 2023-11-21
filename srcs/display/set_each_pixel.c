#include "display.h"

void	set_each_pixel_color(t_mlx *mlxs, const int y, const int x, t_scene *scene)
{
	int	color;

	(void) scene;
	color = 0x00ff0000;
	my_mlx_pixel_put(mlxs->image, y, x, color);
}
