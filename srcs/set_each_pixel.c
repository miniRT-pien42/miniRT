#include "display.h"

void	set_each_pixel_color(t_mlx *mlxs, const int y, const int x)
{
	int	color;

	color = 0x00ff0000;
	my_mlx_pixel_put(mlxs->image, y, x, color);
}
