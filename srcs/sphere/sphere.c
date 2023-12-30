#include "helpers.h"
#include "object.h"
#include "parse.h"
#include "result.h"

t_sphere	*init_sphere(const char **line, t_result *result)
{
	t_sphere	*sphere;

	*result = SUCCESS;
	sphere = (t_sphere *)x_malloc(sizeof(t_sphere));
	sphere->type = SPHERE;
	sphere->center = convert_line_to_vector(line[0], result);
	sphere->diameter = convert_to_double(line[1], result);
	sphere->color = convert_line_to_rgb(line[2], result);
	return (sphere);
}
