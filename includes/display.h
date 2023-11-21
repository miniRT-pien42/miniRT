#ifndef DISPLAY_H
# define DISPLAY_H

# define WIN_TITLE	"miniRT"
# define WIN_HEIGHT	512
# define WIN_WIDTH	512

# define UNREACHABLE	0

typedef struct s_scene	t_scene;
typedef struct s_display {
	void	*mlx_p;
	void	*win_p;
}	t_display;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_mlx {
	t_display	*display;
	t_image		*image;
}	t_mlx;

/* init */
void	init_mlxs(t_mlx *mlxs, t_display *display, t_image *image);

/* display */
void	my_mlx_pixel_put(\
					t_image *image, const int y, const int x, const int color);
void	display_img(t_scene *scene);

/* set */
void	set_each_pixel_color(\
					t_mlx *mlxs, const int y, const int x, t_scene *scene);

#endif
