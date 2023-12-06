#include "libft.h"
#include "object.h"
#include "parse.h"
#include <stdlib.h> // todo: rm (atof)

t_plane	*init_plane(const char **line)
{
	t_plane	*plane;

	plane = (t_plane *)x_malloc(sizeof(t_plane));
	plane->type = PLANE;
	plane->point = convert_line_to_vector(line[1], ',');
	plane->normal = convert_line_to_vector(line[2], ',');
	plane->color = convert_line_to_rgb(line[3], ',');
	return (plane);
}
