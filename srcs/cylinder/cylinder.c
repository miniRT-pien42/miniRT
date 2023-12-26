#include "libft.h"
#include "object.h"
#include "parse.h"
#include <stdlib.h> // todo: rm (atof)

t_cylinder	*init_cylinder(const char **line)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)x_malloc(sizeof(t_cylinder));
	cylinder->type = CYLINDER;
	cylinder->center = convert_line_to_vector(line[1]);
	cylinder->normal = convert_line_to_vector(line[2]);
	cylinder->diameter = atof(line[3]);
	cylinder->height = atof(line[4]);
	cylinder->color = convert_line_to_rgb(line[5]);
	return (cylinder);
}
