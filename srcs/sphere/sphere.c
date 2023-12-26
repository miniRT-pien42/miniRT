#include "libft.h"
#include "object.h"
#include "parse.h"
#include "result.h"
#include <stdlib.h> // todo: rm (atof)

// todo: set result
t_sphere	*init_sphere(const char **line, t_result *result)
{
	t_sphere	*sphere;

	*result = SUCCESS;
	sphere = (t_sphere *)x_malloc(sizeof(t_sphere));
	sphere->type = SPHERE;
	sphere->center = convert_line_to_vector(line[1]);
	sphere->diameter = atof(line[2]);
	sphere->color = convert_line_to_rgb(line[3]);
	return (sphere);
}
