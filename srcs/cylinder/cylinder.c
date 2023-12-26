#include "libft.h"
#include "object.h"
#include "parse.h"
#include "result.h"
#include <stdlib.h> // todo: rm (atof)

// todo: set result
t_cylinder	*init_cylinder(const char **line, t_result *result)
{
	t_cylinder	*cylinder;

	*result = SUCCESS;
	cylinder = (t_cylinder *)x_malloc(sizeof(t_cylinder));
	cylinder->type = CYLINDER;
	cylinder->center = convert_line_to_vector(line[1]);
	cylinder->normal = convert_line_to_vector(line[2]);
	cylinder->diameter = atof(line[3]);
	cylinder->height = atof(line[4]);
	cylinder->color = convert_line_to_rgb(line[5]);
	return (cylinder);
}
