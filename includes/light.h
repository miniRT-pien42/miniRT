#ifndef LIGHT_H
# define LIGHT_H

# include "color.h"
# include "result.h"
# include "vector.h"

typedef struct s_light_ambient
{
	double	bright;
	t_rgb	color;
}	t_light_ambient;

// color: unused in mandatory
typedef struct s_light
{
	t_vector	pos;
	double		bright;
	t_rgb		color;
}	t_light;

/* light */
t_light_ambient	*init_light_ambient(const char **line, t_result *result);
t_light			*init_light(const char **line, t_result *results);

#endif
