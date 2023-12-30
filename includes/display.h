#ifndef DISPLAY_H
# define DISPLAY_H

#include "vector.h"
#include "quaternion.h"
#include <stdlib.h>//size_t

# define TITLE	"miniRT"
# define HEIGHT	512
# define WIDTH	512

# define UNREACHABLE	0

typedef struct s_scene	t_scene;
typedef struct s_rgb	t_rgb;
typedef struct s_ray	t_ray;

typedef struct s_display
{
	void	*mlx_p;
	void	*win_p;
}	t_display;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_mlx
{
	t_display	*display;
	t_image		*image;
	t_scene		*scene;
}	t_mlx;

typedef struct s_screen_info
{
	size_t			x;
	size_t			y;
	t_vector		center_screen;
	t_vector		axis;
	t_quaternion	q_rotate;
}	t_screen_info;

/* init */
void	init_mlxs(\
	t_mlx *mlxs, t_display *display, t_image *image, t_scene *scene);

/* display */
void	my_mlx_pixel_put(\
	t_image *image, const int y, const int x, const int color);
void	display(t_scene *scene);

/* ray_trace */
t_rgb	ray_tracing(t_scene *scene, void *nearest_object, const t_ray *ray);

/* set */
void		set_each_pixel_color(t_mlx *mlxs, t_scene *scene, t_screen_info screen);

#endif
