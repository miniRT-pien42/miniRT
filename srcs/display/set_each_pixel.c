#include "display.h"
#include "scene.h"

void	set_each_pixel_color(t_mlx *mlxs, const int y, const int x, t_scene *scene)
{
	int	color;

	if (is_intersect_to_sphere(y, x, scene))
		color = COLOR_RED;
	else
		color = COLOR_BLUE;
	my_mlx_pixel_put(mlxs->image, y, x, color);
}
