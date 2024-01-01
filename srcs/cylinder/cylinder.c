#include "helpers.h"
#include "object.h"
#include "parse.h"

t_cylinder	*init_cylinder(const char **line, t_result *result)
{
	t_cylinder	*cylinder;

	*result = SUCCESS;
	cylinder = (t_cylinder *)x_malloc(sizeof(t_cylinder));
	cylinder->type = CYLINDER;
	cylinder->center = convert_line_to_vector(line[0], result);
	cylinder->normal = \
		init_normal_vector(line[1], DIR_N_MIN, DIR_N_MAX, result);
	cylinder->diameter = convert_to_double(line[2], result);
	cylinder->height = convert_to_double(line[3], result);
	cylinder->color = convert_line_to_rgb(line[4], result);
	return (cylinder);
}
