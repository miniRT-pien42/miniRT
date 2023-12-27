#include "libft.h"
#include "object.h"
#include "parse.h"
#include <stdlib.h> // todo: rm (atof)

t_sphere	*init_sphere(const char **line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)x_malloc(sizeof(t_sphere));
	sphere->type = SPHERE;
	sphere->center = convert_line_to_vector(line[1]);
	sphere->diameter = atof(line[2]);
	sphere->color = convert_line_to_rgb(line[3]);
	return (sphere);
}
