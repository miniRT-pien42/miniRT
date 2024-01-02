#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

# define COLOR_MASK		0xFF
# define RED_SHIFT		16
# define GREEN_SHIFT	8

typedef enum e_color
{
	COLOR_WHITE = 0x00ffffff,
	COLOR_RED = 0x00ff0000,
	COLOR_PINK = 0x00f189df,
	COLOR_YELLOW = 0x00f2ec5a,
	COLOR_GREEN = 0x0061ff76,
	COLOR_BLUE = 0x002a89df,
}	t_color;

typedef struct s_rgb
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_rgb;

typedef struct s_rgb_f
{
	double	r;
	double	g;
	double	b;
}	t_rgb_f;

/* color */
int	convert_rgb(t_rgb color);

#endif
