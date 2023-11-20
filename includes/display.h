#ifndef DISPLAY_H
# define DISPLAY_H

# define WIN_TITLE	"miniRT"
# define WIN_HEIGHT	512
# define WIN_WIDTH	512

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

#endif
