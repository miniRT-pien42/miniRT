#ifndef DISPLAY_H
# define DISPLAY_H

# include "vector.h"

# define TITLE	"miniRT"
# define HEIGHT	512
# define WIDTH	512

# define AXIS_BASE_X	0.0
# define AXIS_BASE_Y	-1.0
# define AXIS_BASE_Z	0.0

# define AXIS_ROTATE_BASE_X	0.0
# define AXIS_ROTATE_BASE_Y	0.0
# define AXIS_ROTATE_BASE_Z	1.0

# define UNREACHABLE	0
# define KEY_NONE		0

typedef struct s_ray	t_ray;
typedef struct s_rgb	t_rgb;
typedef struct s_scene	t_scene;

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
	int				x;
	int				y;
	t_vector		center_screen;
	double			rotate_x;
	double			rotate_y;
}	t_screen_info;

/* init */
void			init_mlxs(\
	t_mlx *mlxs, t_display *display, t_image *image, t_scene *scene);

/* display */
void			my_mlx_pixel_put(\
	t_image *image, const int y, const int x, const int color);
void			display(t_scene *scene);

/* hook */
void			set_hook(t_mlx *mlxs);

/* ray_trace */
t_rgb			ray_tracing(\
	t_scene *scene, void *nearest_object, const t_ray *ray);

/* screen */
t_vector		set_axis_base(void);
t_vector		set_axis_rotate_base(void);
t_screen_info	get_screen_info(t_scene *scene);

/* screen_rotate */
double			get_rotate_x(t_vector direction);
double			get_rotate_y(t_vector direction);
t_vector		rotate_vector_x(t_vector v, const double angle);
t_vector		rotate_vector_y(t_vector v, const double angle);

/* set */
void			set_each_pixel_color(\
	t_mlx *mlxs, t_scene *scene, t_screen_info screen);

#endif
