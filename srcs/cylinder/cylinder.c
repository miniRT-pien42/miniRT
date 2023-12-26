#include "libft.h"
#include "object.h"
#include "parse.h"
#include "result.h"
#include <stdlib.h> // todo: rm (atof)

// todo: set result with atof
t_cylinder	*init_cylinder(const char **line, t_result *result)
{
	t_cylinder	*cylinder;

	*result = SUCCESS;
	cylinder = (t_cylinder *)x_malloc(sizeof(t_cylinder));
	cylinder->type = CYLINDER;
	cylinder->center = convert_line_to_vector(line[0], result);
	cylinder->normal = convert_line_to_vector_in_range(\
										line[1], DIR_N_MIN, DIR_N_MAX, result);
	cylinder->diameter = atof(line[2]);
	cylinder->height = atof(line[3]);
	cylinder->color = convert_line_to_rgb(line[4], result);
	return (cylinder);
}
