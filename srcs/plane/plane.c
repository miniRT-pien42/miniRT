#include "libft.h"
#include "object.h"
#include "parse.h"
#include "result.h"

// todo: set result
t_plane	*init_plane(const char **line, t_result *result)
{
	t_plane	*plane;

	*result = SUCCESS;
	plane = (t_plane *)x_malloc(sizeof(t_plane));
	plane->type = PLANE;
	plane->point = convert_line_to_vector(line[1]);
	plane->dir_n = convert_line_to_vector(line[2]);
	plane->color = convert_line_to_rgb(line[3]);
	return (plane);
}
