#include "libft.h"
#include "light.h"
#include "parse.h"
#include "result.h"

t_light_ambient	*init_light_ambient(const char **line, t_result *result)
{
	t_light_ambient	*light_ambient;

	light_ambient = (t_light_ambient *)x_malloc(sizeof(t_light_ambient));
	light_ambient->bright = convert_to_double_in_range(\
										line[1], RATIO_MIN, RATIO_MAX, result);
	light_ambient->color = convert_line_to_rgb(line[2], result);
	return (light_ambient);
}

t_light	*init_light(const char **line, t_result *result)
{
	t_light	*light;

	light = (t_light *)x_malloc(sizeof(t_light));
	light->pos = convert_line_to_vector(line[1], result);
	light->bright = convert_to_double_in_range(\
										line[2], RATIO_MIN, RATIO_MAX, result);
	return (light);
}
