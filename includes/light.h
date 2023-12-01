#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h"
# include "color.h"

typedef struct s_light_ambient
{
	double	bright;
	t_rgb	color;
}	t_light_ambient;

typedef struct s_light
{
	t_vector	pos;
	double		bright;
}	t_light;

t_light_ambient	*init_light_ambient(const char **line);
t_light			*init_light(const char **line);

#endif
