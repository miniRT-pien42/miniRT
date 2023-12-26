#include "libft.h"
#include "light.h"
#include "parse.h"
#include <stdlib.h> // todo: rm (atof)

t_light_ambient	*init_light_ambient(const char **line)
{
	t_light_ambient	*light_ambient;

	light_ambient = (t_light_ambient *)x_malloc(sizeof(t_light_ambient));
	light_ambient->bright = atof(line[1]);
	light_ambient->color = convert_line_to_rgb(line[2]);
	return (light_ambient);
}

t_light	*init_light(const char **line)
{
	t_light	*light;

	light = (t_light *)x_malloc(sizeof(t_light));
	light->pos = convert_line_to_vector(line[1]);
	light->bright = atof(line[2]);
	return (light);
}
